#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <string>
#include "../Game/Game.hpp"
#include "../ECS/ECS.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/DrawableComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/ProjectileComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Systems/EnemySystem.hpp"
#include "../Systems/HealthSystem.hpp"
#include "../Systems/EnemySystem.hpp"
#include "../Systems/ChargeManageSystem.hpp"
#include "../Systems/DrawingEffectSystem.hpp"
#include "../Systems/RenderTextSystem.hpp"
#include <chrono>

/**
 * @brief Checks if a specific action is activated in the controller manager.
 * @param action The name of the action to check.
 * @return True if the action is activated, false otherwise.
 */
bool IsActionActivated(const std::string& action) {
    return Game::GetInstance().controllerManager->IsActionActivated(action);
}

/**
 * @brief Checks if a specific mouse button is pressed.
 * @param button_name The name of the mouse button to check.
 * @return True if the mouse button is down, false otherwise.
 */
bool IsMouseButtonDown(const std::string& button_name) {
    return Game::GetInstance().controllerManager->IsMouseButtonDown(button_name);
}
/**
 * @brief Retrieves the current mouse position.
 * @return A tuple containing the x and y coordinates of the mouse.
 */
std::tuple<int, int> GetMousePosition() {
    return Game::GetInstance().controllerManager->GetMousePosition();
}
/**
 * @brief Retrieves the position of the player entity.
 * @return A tuple containing the x and y coordinates of the player, or (0, 0) if not found.
 */
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

/**
 * @brief Retrieves the position of a given enemy entity.
 * @param self The enemy entity to query.
 * @return A tuple containing the x and y coordinates of the enemy, or (0, 0) if no transform component is found.
 */
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
/**
 * @brief Retrieves the position of an enemy entity by its ID.
 * @param id The ID of the enemy entity.
 * @return A tuple containing the x and y coordinates of the enemy, or (0, 0) if not found or no transform component.
 */
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
/**
 * @brief Pushes a table of all enemy entity IDs to the Lua stack.
 * @param L The Lua state.
 * @return The number of results pushed to the Lua stack (1 for the table).
 */
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
/**
 * @brief Performs a melee attack from an attacker entity targeting the player.
 * @param attacker The entity performing the melee attack.
 */
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
/**
 * @brief Performs a ranged attack from an attacker entity, creating a projectile.
 * @param attacker The entity performing the ranged attack.
 */
void AttackRanger(Entity attacker) {
    auto& registry = Game::GetInstance().registry;
    if (!attacker.HasComponent<HealthComponent>()) return;

    // Obtener entidades manejadas por HealthSystem
    auto entities = registry->GetEntitiesFromSystem<EnemySystem>();

    for (auto& entity : entities) { // buggeado
        if (entity.HasComponent<ProjectileComponent>() && entity.GetComponent<SpriteComponent>().active == false) {

            auto& health = attacker.GetComponent<HealthComponent>();
            float damageInterval = health.attackTimeout;
            // Obtener tiempo actual
            auto now = std::chrono::steady_clock::now();
            
            // Calcular tiempo transcurrido desde el último daño recibido por esta entidad específica
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - attacker.GetComponent<HealthComponent>().attackTimeoutDuration).count();
            int intervalMs = static_cast<int>(damageInterval * 1000); //damageInterval es tiempos de disparos
            
            // Si no ha pasado suficiente tiempo, no aplicar daño
            if (elapsed < intervalMs) {
                return;
            }
            attacker.GetComponent<HealthComponent>().attackTimeoutDuration = now;
            auto& ene = registry->GetSystem<EnemySystem>();
            std::tuple<int, int> playerPos = GetPlayerPosition();
            glm::vec2 enemyPosition = attacker.GetComponent<TransformComponent>().position;

            // Convertir posición del jugador a vec2
            glm::vec2 playerPosition = glm::vec2(std::get<0>(playerPos), std::get<1>(playerPos));

            // Calcular el vector dirección del enemigo hacia el jugador
            glm::vec2 direction = playerPosition - enemyPosition;

            // Normalizar la dirección para obtener el vector unitario
            glm::vec2 normalizedDirection = glm::normalize(direction);

            // Definir la velocidad del proyectil (ajusta este valor según tu juego)
            float projectileSpeed = 100.0f; // pixels per second, por ejemplo

            // Calcular la velocidad final
            glm::vec2 velocity = normalizedDirection * projectileSpeed;

            // Calcular la rotación en radianes usando atan2
            double arrowRotation = atan2(direction.y, direction.x);

            // Si necesitas la rotación en grados en lugar de radianes:
            double arrowRotationDegrees = glm::degrees(arrowRotation);
            ene.CreateEnemyProjectile(registry, velocity, enemyPosition, arrowRotationDegrees, attacker.GetComponent<HealthComponent>().damage);
        }
    }
}
/**
 * @brief Sets the current game level.
 * @param level The level number to set.
 */
void SetLevel(int level) {
    Game::GetInstance().currentLevel = level;
}
/**
 * @brief Updates the current draw index and manages sprite visibility for charge components.
 * @param entity The entity associated with the draw action.
 * @param index The new draw index.
 */
void CurrentDrawIndex(Entity entity, int index) {

    if (Game::GetInstance().drawIndex == -1) {
        Game::GetInstance().drawIndex = index;
        auto& registry = Game::GetInstance().registry;
        for (auto entity : registry->GetSystem<RenderTextSystem>().GetSystemEntities()) {
            if (entity.HasComponent<DamageChargeComponent>() || entity.HasComponent<SprintChargeComponent>() || entity.HasComponent<SlowChargeComponent>() ) {
                if (entity.HasComponent<DamageChargeComponent>() && index == 0) {
                    entity.GetComponent<SpriteComponent>().active = true;
                } else if (entity.HasComponent<SprintChargeComponent>() && index == 1) {
                    entity.GetComponent<SpriteComponent>().active = true;
                } else if (entity.HasComponent<SlowChargeComponent>() && index == 2) {
                    entity.GetComponent<SpriteComponent>().active = true;
                }
                
            }
        }
    } else {
        int prevIndex = Game::GetInstance().drawIndex;
        Game::GetInstance().drawIndex = index;
        auto& registry = Game::GetInstance().registry;

        for (auto entity : registry->GetSystem<RenderTextSystem>().GetSystemEntities()) {
            if (entity.HasComponent<DamageChargeComponent>() || entity.HasComponent<SprintChargeComponent>() || entity.HasComponent<SlowChargeComponent>() ) {
                if (entity.HasComponent<DamageChargeComponent>() && index == 0) {

                    entity.GetComponent<SpriteComponent>().active = true;
                } else if (entity.HasComponent<SprintChargeComponent>() && index == 1) {
                    entity.GetComponent<SpriteComponent>().active = true;
                } else if (entity.HasComponent<SlowChargeComponent>() && index == 2) {
                    entity.GetComponent<SpriteComponent>().active = true;
                } else if (entity.HasComponent<DamageChargeComponent>() && prevIndex == 0) {

                    entity.GetComponent<SpriteComponent>().active = false;
                } else if (entity.HasComponent<SprintChargeComponent>() && prevIndex == 1) {
                    entity.GetComponent<SpriteComponent>().active = false;
                } else if (entity.HasComponent<SlowChargeComponent>() && prevIndex == 2) {
                    entity.GetComponent<SpriteComponent>().active = false;
                }
                
            }
        }
    }
    

}



/**
 * @brief Sets the velocity of an entity's RigidBodyComponent.
 * @param entity The entity to modify.
 * @param x The x-component of the velocity.
 * @param y The y-component of the velocity.
 */

void SetVelocity(Entity entity, float x, float y) {
    auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
    rigidBody.velocity.x = x;
    rigidBody.velocity.y = y;
}
/**
 * @brief Transitions to a new scene in the game.
 * @param sceneName The name of the scene to transition to.
 */
void GoToScene(const std::string& sceneName) {
    Game::GetInstance().sceneManager->SetNextScene(sceneName);
    Game::GetInstance().sceneManager->StopScene();
}
/**
 * @brief Adds a draw point to an entity's DrawableComponent if sufficient charge is available.
 * @param entity The entity to add the draw point to.
 * @param index The index of the color point array.
 * @param x The x-coordinate of the draw point.
 * @param y The y-coordinate of the draw point.
 */
void PushDrawPoint(Entity entity, int index, int x, int y) {
    auto& draw = entity.GetComponent<DrawableComponent>();
    if (index >= 0 && index < (int)draw.colorPoints.size() && Game::GetInstance().registry->GetSystem<ChargeManageSystem>().HasSufficientCharge(index) == true) {
        // TODO: aunque no se dibujen igual se cuentan (hacer chequeo de la posicion (menor a 70/75 en Y))
        draw.colorPoints[index].emplace_back(glm::vec2(x, y), std::chrono::steady_clock::now());
        Game::GetInstance().registry->GetSystem<ChargeManageSystem>().ConsumeChargeForDrawing(index);
    }
}

#endif // LUABINDING_HPP