#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <string>
#include "../Game/Game.hpp"
#include "../ECS/ECS.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/DrawableComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Systems/HealthSystem.hpp"
#include "../Systems/EnemySystem.hpp"
#include "../Systems/ChargeManageSystem.hpp"
#include <chrono>
bool IsActionActivated(const std::string& action) {
    return Game::GetInstance().controllerManager->IsActionActivated(action);
}

// Mouse
bool IsMouseButtonDown(const std::string& button_name) {
    return Game::GetInstance().controllerManager->IsMouseButtonDown(button_name);
}

std::tuple<int, int> GetMousePosition() {
    return Game::GetInstance().controllerManager->GetMousePosition();
}
std::tuple<int, int> GetPlayerPosition() {
    auto& registry = Game::GetInstance().registry;

    // Obtener todas las entidades gestionadas por HealthSystem
    auto entities = registry->GetEntitiesFromSystem<HealthSystem>();

    for (auto& entity : entities) {
        if (entity.HasComponent<HealthComponent>()) {
            auto& health = entity.GetComponent<HealthComponent>();
            if (health.isPlayer && entity.HasComponent<TransformComponent>()) {
                auto& transform = entity.GetComponent<TransformComponent>();
                return std::make_tuple(
                    static_cast<int>(transform.position.x),
                    static_cast<int>(transform.position.y)
                );
            }
        }
    }

    // Si no se encuentra el jugador, retornar 0,0
    return std::make_tuple(0, 0);
}


std::tuple<int, int> GetEnemyPosition(Entity self) {
    if (self.HasComponent<TransformComponent>()) {
        auto& transform = self.GetComponent<TransformComponent>();
        return std::make_tuple(
            static_cast<int>(transform.position.x),
            static_cast<int>(transform.position.y)
        );
    }

    // Si no tiene componente de posición, devolver por defecto
    return std::make_tuple(0, 0);
}
std::tuple<int, int> GetEnemyPositionById(int id) {
    auto& registry = Game::GetInstance().registry;
    auto entities = registry->GetEntitiesFromSystem<EnemySystem>();
    
    for (const auto& entity : entities) {
        if (entity.GetId() == id) {
            if (entity.HasComponent<TransformComponent>()) {
                auto& transform = entity.GetComponent<TransformComponent>();
                return std::make_tuple(
                    static_cast<int>(transform.position.x),
                    static_cast<int>(transform.position.y)
                );
            }
            break; // Encontramos la entidad, pero no tiene TransformComponent
        }
    }
    // No se encontró la entidad o no tiene TransformComponent
    return std::make_tuple(0, 0);
}
int GetAllEnemies(lua_State* L) {
    auto& registry = Game::GetInstance().registry;
    auto entities = registry->GetEntitiesFromSystem<EnemySystem>();

    lua_newtable(L);
    int index = 1;
    for (const auto& entity : entities) {
        lua_pushinteger(L, static_cast<lua_Integer>(entity.GetId()));
        lua_rawseti(L, -2, index);
        index++;
    }

    return 1;
}

void AttackMelee(Entity attacker) {
    auto& registry = Game::GetInstance().registry;

    if (!attacker.HasComponent<HealthComponent>()) return;

    Entity playerEntity(-1);
    bool foundPlayer = false;

    // Obtener entidades manejadas por HealthSystem
    auto entities = registry->GetEntitiesFromSystem<HealthSystem>();

    for (auto& entity : entities) {
        if (entity.HasComponent<HealthComponent>()) {
            auto& health = entity.GetComponent<HealthComponent>();
            if (health.isPlayer) {
                playerEntity = entity;
                foundPlayer = true;
                break;
            }
        }
    }

    if (foundPlayer && playerEntity.HasComponent<HealthComponent>()) {
        auto& attackerHealth = attacker.GetComponent<HealthComponent>();
        auto& healthSystem = registry->GetSystem<HealthSystem>();
        healthSystem.ReduceHP(playerEntity, attackerHealth.damage, attacker);
    }
}





//RigidBody component

void SetVelocity(Entity entity, float x, float y) {
    auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
    rigidBody.velocity.x = x;
    rigidBody.velocity.y = y;
}

void GoToScene(const std::string& sceneName) {
    Game::GetInstance().sceneManager->SetNextScene(sceneName);
    Game::GetInstance().sceneManager->StopScene();
}

void PushDrawPoint(Entity entity, int index, int x, int y) {
    auto& draw = entity.GetComponent<DrawableComponent>();
    if (index >= 0 && index < (int)draw.colorPoints.size() && Game::GetInstance().registry->GetSystem<ChargeManageSystem>().HasSufficientCharge(index) == true) {
        // Añadimos el punto con el timestamp
        draw.colorPoints[index].emplace_back(glm::vec2(x, y), std::chrono::steady_clock::now());
        Game::GetInstance().registry->GetSystem<ChargeManageSystem>().ConsumeChargeForDrawing(index);
    }
}

#endif // LUABINDING_HPP