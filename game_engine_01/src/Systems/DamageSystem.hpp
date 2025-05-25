#ifndef DAMAGESYSTEM_HPP
#define DAMAGESYSTEM_HPP

#include <memory>
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/ProjectileComponent.hpp"

#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

class DamageSystem : public System {
    public:
    DamageSystem() {
        RequireComponent<CircleColliderComponent>();
    }
    void SubscribeToCollisionEvent(std::unique_ptr<EventManager>& eventManager) {
        eventManager->SubscribeToEvent<DamageSystem, CollisionEvent>(this, &DamageSystem::OnCollision);
    }


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