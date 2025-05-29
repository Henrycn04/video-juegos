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

/**
 * @brief Handles circular collision detection between entities
 * 
 * Detects collisions between entities with CircleColliderComponent
 * and TransformComponent, emitting CollisionEvents when collisions occur.
 */
class CollisionSystem : public System {
public:
    /**
     * @brief Construct a new Collision System object
     * 
     * Requires entities to have both CircleColliderComponent and TransformComponent
     */
    CollisionSystem() {
        RequireComponent<CircleColliderComponent>();
        RequireComponent<TransformComponent>();
    }

    /**
     * @brief Update collision detection for all entities
     * @param eventManager Reference to the event manager for emitting collision events
     */
    void Update(std::unique_ptr<EventManager>& eventManager) {
        auto entities = GetSystemEntities();
        
        // Check all entity pairs for collisions (n^2/2 checks)
        for (auto i = entities.begin(); i != entities.end(); ++i) {
            auto entityA = *i;
            auto transformA = entityA.GetComponent<TransformComponent>();
            auto colliderA = entityA.GetComponent<CircleColliderComponent>();
            
            for (auto j = std::next(i); j != entities.end(); ++j) {
                auto entityB = *j;
                
                auto transformB = entityB.GetComponent<TransformComponent>();
                auto colliderB = entityB.GetComponent<CircleColliderComponent>();
                
                // Calculate world-space centers including scale and offset
                glm::vec2 centerA = glm::vec2(
                    transformA.position.x + (colliderA.width / 2.0f) * transformA.scale.x,
                    transformA.position.y + (colliderA.height / 2.0f) * transformA.scale.y
                );
                
                glm::vec2 centerB = glm::vec2(
                    transformB.position.x + (colliderB.width / 2.0f) * transformB.scale.x,
                    transformB.position.y + (colliderB.height / 2.0f) * transformB.scale.y
                );
                
                // Calculate scaled radii
                float aRadius = colliderA.radius * transformA.scale.x;
                float bRadius = colliderB.radius * transformB.scale.x;
                
                // Check for collision
                bool collision = CheckCircularCollision(aRadius, bRadius, centerA, centerB);
                
                if (collision) {
                    eventManager->EmitEvent<CollisionEvent>(entityA, entityB);
                }
            }
        }
    }

private:
    /**
     * @brief Check if two circles are colliding
     * @param aRadius Radius of first circle
     * @param bRadius Radius of second circle
     * @param aPos Center position of first circle
     * @param bPos Center position of second circle
     * @return true if circles are colliding
     * @return false if circles are not colliding
     */
    bool CheckCircularCollision(float aRadius, float bRadius, const glm::vec2& aPos, const glm::vec2& bPos) {
        glm::vec2 diff = aPos - bPos;
        float distanceSquared = diff.x * diff.x + diff.y * diff.y;
        float radiusSum = aRadius + bRadius;
        
        // Compare squared distances to avoid sqrt operation
        return (radiusSum * radiusSum) >= distanceSquared;
    }
};

#endif // COLLISIONSYSTEM_HPP