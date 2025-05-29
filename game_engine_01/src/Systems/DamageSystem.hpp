#ifndef DAMAGESYSTEM_HPP
#define DAMAGESYSTEM_HPP

#include <memory>
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/ProjectileComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

/**
 * @brief System that handles damage application when collisions occur
 * 
 * Listens for collision events and applies damage when:
 * - A projectile hits an entity with health
 * - The damaged entity is a player
 * Manages player death state when health reaches zero.
 */
class DamageSystem : public System {
    public:
    /**
     * @brief Construct a new Damage System object
     * 
     * Requires entities to have CircleColliderComponent
     */
    DamageSystem() {
        RequireComponent<CircleColliderComponent>();
    }
    /**
     * @brief Subscribe to collision events
     * @param eventManager Reference to the event manager
     */
    void SubscribeToCollisionEvent(std::unique_ptr<EventManager>& eventManager) {
        eventManager->SubscribeToEvent<DamageSystem, CollisionEvent>(this, &DamageSystem::OnCollision);
    }

    /**
     * @brief Handle collision events and apply damage
     * @param event The collision event containing involved entities
     */
    void OnCollision(CollisionEvent& event) {
        if (event.entityA.HasComponent<HealthComponent>() && event.entityB.HasComponent<ProjectileComponent>()) {
            auto& health = event.entityA.GetComponent<HealthComponent>();
            auto& arrow = event.entityB.GetComponent<HealthComponent>();
            

            
            if (health.isPlayer) {
                health.health -= arrow.damage;
                if (health.health <= 0) {
                    health.health = 0;
                    Game::GetInstance().finDelNivel = true;
                    Game::GetInstance().win = false;
                }
                event.entityB.Kill();
            }
        } else if (event.entityB.HasComponent<HealthComponent>() && event.entityA.HasComponent<ProjectileComponent>()) {
            auto& health = event.entityB.GetComponent<HealthComponent>();
            auto& arrow = event.entityA.GetComponent<HealthComponent>();
            
            if (health.isPlayer) {
                health.health -= arrow.damage;
                if (health.health <= 0) {
                    health.health = 0;
                    Game::GetInstance().finDelNivel = true;
                    Game::GetInstance().win = false;
                }
                event.entityA.Kill();
            }
        }
    }
    


};

#endif