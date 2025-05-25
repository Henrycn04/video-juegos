#ifndef COLLISIONSYSTEM_HPP
#define COLLISIONSYSTEM_HPP
#include "../ECS/ECS.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/ProjectileComponent.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"
#include <iostream>
#include <memory>

class CollisionSystem : public System {
public:
    CollisionSystem() {
        RequireComponent<CircleColliderComponent>();
        RequireComponent<TransformComponent>();
    }

    void Update(std::unique_ptr<EventManager>& eventManager) {
        auto entities = GetSystemEntities();
        
        for (auto i = entities.begin(); i != entities.end(); ++i) {
            auto entityA = *i;
            auto transformA = entityA.GetComponent<TransformComponent>();
            auto colliderA = entityA.GetComponent<CircleColliderComponent>();
            
            for (auto j = std::next(i); j != entities.end(); ++j) {
                auto entityB = *j;
                
                // Esta verificación es redundante ya que j siempre viene después de i
                // if (entityA == entityB) continue;
                
                auto transformB = entityB.GetComponent<TransformComponent>();
                auto colliderB = entityB.GetComponent<CircleColliderComponent>();
                
                // Cálculo correcto del centro: posición + offset del centro
                glm::vec2 centerA = glm::vec2(
                    transformA.position.x + (colliderA.width / 2.0f) * transformA.scale.x,
                    transformA.position.y + (colliderA.height / 2.0f) * transformA.scale.y
                );
                
                // CORREGIDO: Paréntesis mal colocado aquí
                glm::vec2 centerB = glm::vec2(
                    transformB.position.x + (colliderB.width / 2.0f) * transformB.scale.x,
                    transformB.position.y + (colliderB.height / 2.0f) * transformB.scale.y
                );
                
                // Cálculo correcto del radio escalado
                float aRadius = colliderA.radius * transformA.scale.x;
                float bRadius = colliderB.radius * transformB.scale.x;
                
                bool collision = CheckCircularCollision(aRadius, bRadius, centerA, centerB);
                
                if (collision) {
                    eventManager->EmitEvent<CollisionEvent>(entityA, entityB);
                }
            }
        }
    }

private:
    bool CheckCircularCollision(float aRadius, float bRadius, const glm::vec2& aPos, const glm::vec2& bPos) {
        glm::vec2 diff = aPos - bPos;
        float distanceSquared = diff.x * diff.x + diff.y * diff.y;
        float radiusSum = aRadius + bRadius;
        
        // Evitar sqrt comparando distancias al cuadrado
        return (radiusSum * radiusSum) >= distanceSquared;
    }
};

#endif