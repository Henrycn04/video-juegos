#ifndef ENEMYSYSTEM_HPP
#define ENEMYSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/EnemyComponent.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/DrawableComponent.hpp"
#include "../Components/EnemyComponent.hpp"
#include "../Components/EffectReceiverComponent.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/ProjectileComponent.hpp"
#include <memory>
#include <cstdlib>

class EnemySystem : public System {
public:
    EnemySystem() {
        RequireComponent<EnemyComponent>();
    }

    void Update(std::unique_ptr<Registry>& registry) {
        Game& game = Game::GetInstance();
        for (auto spawner : GetSystemEntities()) {

            auto& enemySpawner = spawner.GetComponent<EnemyComponent>();

            int currentAlive = CountClonesFrom(spawner.GetId());
            if (currentAlive < enemySpawner.amountToSpawn && enemySpawner.totalAmount > 0) {
                Entity newEnemy = registry->CreateEntity();
                CloneEntityFromTemplate(spawner, newEnemy);
                enemySpawner.totalAmount--;
                game.enemiesLeftToSpawn--;
            }
            

        }

    }

    // este es el disparo como tal, trabajar con rotacion igual
    void CreateEnemyProjectile(std::unique_ptr<Registry>& registry, glm::vec2 velocity, glm::vec2 position, double rotation, int damage) {
        for (auto spawner : GetSystemEntities()) {
            if (spawner.HasComponent<ProjectileComponent>() ) {
                Entity newEnemy = registry->CreateEntity();
                CloneEntityFromTemplate(spawner, newEnemy);
                newEnemy.GetComponent<TransformComponent>().position = position;
                newEnemy.GetComponent<TransformComponent>().rotation = rotation;
                newEnemy.GetComponent<RigidBodyComponent>().velocity = velocity;
                newEnemy.GetComponent<HealthComponent>().damage = damage;
                break;
            }

        }
    }

private:
    int CountClonesFrom(int spawnerId) {
        int count = 0;
        for (auto entity : GetSystemEntities()) {
            auto& enemy = entity.GetComponent<EnemyComponent>();
            if (entity.GetId() != spawnerId && enemy.spawnerId == spawnerId) {
                count++;
            }
        }
        return count;
    }



    void CloneEntityFromTemplate(Entity source, Entity target) {
        // Animation
        if (source.HasComponent<AnimationComponent>()) {
            target.AddComponent<AnimationComponent>(source.GetComponent<AnimationComponent>());
        }

        // Collider
        if (source.HasComponent<CircleColliderComponent>()) {
            target.AddComponent<CircleColliderComponent>(source.GetComponent<CircleColliderComponent>());
        }

        // Health
        if (source.HasComponent<HealthComponent>()) {
            target.AddComponent<HealthComponent>(source.GetComponent<HealthComponent>());
        }

        // Rigidbody
        if (source.HasComponent<RigidBodyComponent>()) {
            target.AddComponent<RigidBodyComponent>(source.GetComponent<RigidBodyComponent>());
        }

        // Script
        if (source.HasComponent<ScriptComponent>()) {
            auto script = source.GetComponent<ScriptComponent>();
            target.AddComponent<ScriptComponent>(script);
        }

        // Sprite
        if (source.HasComponent<SpriteComponent>()) {
            auto sprite = source.GetComponent<SpriteComponent>();
            sprite.active = true;  // Activar visibilidad para el clon
            target.AddComponent<SpriteComponent>(sprite);
        }

        // Transform con posición aleatoria
        if (source.HasComponent<TransformComponent>()) {
            auto transform = source.GetComponent<TransformComponent>();
            transform.position = GetRandomSpawnPosition();
            target.AddComponent<TransformComponent>(transform);
        }
        if (source.HasComponent<EffectReceiverComponent>()) {
            target.AddComponent<EffectReceiverComponent>(source.GetComponent<EffectReceiverComponent>());
        }
        if (source.HasComponent<TextComponent>()) {
            target.AddComponent<TextComponent>(source.GetComponent<TextComponent>());
        }
        if (source.HasComponent<ProjectileComponent>()) {
            target.AddComponent<ProjectileComponent>(source.GetComponent<ProjectileComponent>());
        }


        // EnemyComponent sin capacidad de spawnear otros
        if (source.HasComponent<EnemyComponent>()) {
            target.AddComponent<EnemyComponent>(source.GetComponent<EnemyComponent>());
            target.GetComponent<EnemyComponent>().amountToSpawn = 0;
            target.GetComponent<EnemyComponent>().spawnerId = source.GetId();
        }
    }

    glm::vec2 GetRandomSpawnPosition() {
        int x, y;

        // Elegir entre izquierda o derecha
        bool leftRight = rand() % 2;
        if (leftRight) {
            x = rand() % 41; // 0 - 40
        } else {
            x = 760 + (rand() % 41); // 760 - 800
        }

        // Elegir entre arriba o abajo
        bool topBottom = rand() % 2;
        if (topBottom) {
            y = 75 + (rand() % 31); // 75 - 105
        } else {
            y = 560 + (rand() % 41); // 560 - 600
        }

        return glm::vec2(static_cast<float>(x), static_cast<float>(y));
    }
};

#endif
