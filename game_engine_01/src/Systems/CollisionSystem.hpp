#ifndef COLLISIONSYSTEM_HPP
#define COLLISIONSYSTEM_HPP
#include "../ECS/ECS.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/TransformComponent.hpp"
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
                    if (entityA == entityB) {
                        continue;
                    }
                    auto transformB = entityB.GetComponent<TransformComponent>();
                    auto colliderB = entityB.GetComponent<CircleColliderComponent>();

                    glm::vec2 centerA = glm::vec2( //TODO:: problemas con multiplicacion de transform // Circular pt2
                        transformA.position.x - ((colliderA.width / 2) * transformA.scale.x / 2),
                        transformA.position.y - ((colliderA.height / 2) * transformA.scale.y / 2)
                    );
                    glm::vec2 centerB = glm::vec2(
                        transformB.position.x - ((colliderB.width / 2) * transformB.scale.x / 2),
                        transformB.position.y - ((colliderB.height / 2) * transformB.scale.y) / 2
                    );
                    int aRadius = colliderA.radius * transformA.scale.x / 2;
                    int bRadius = colliderB.radius  * transformB.scale.x / 2;
                    bool collision = CheckCircularCollision(
                        aRadius,
                        bRadius,
                        centerA,
                        centerB
                    );
                    if (collision) {
                        eventManager->EmitEvent<CollisionEvent>(entityA, entityB);
                    }
                }
            }
        }
        bool CheckCircularCollision(int aRadius, int bRadius, glm::vec2 aPos, glm::vec2 bPos) {
            glm::vec2 dif = aPos - bPos;
            double length = glm::sqrt((dif.x * dif.x) + (dif.y * dif.y));
            return ((aRadius + bRadius) >= length);
        } 
};

#endif