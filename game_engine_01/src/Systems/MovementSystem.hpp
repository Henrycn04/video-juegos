#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

class MovementSystem : public System {
    public:
        MovementSystem() {
            RequireComponent<RigidBodyComponent>();
            RequireComponent<TransformComponent>();
        }

        void Update(double dt) {
            for (auto entity : GetSystemEntities()) {
                const auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
                auto& transform = entity.GetComponent<TransformComponent>();

                // Update the position based on velocity and deltaTime
                transform.position.x += rigidBody.velocity.x * dt;
                transform.position.y += rigidBody.velocity.y * dt;
            }
        }

};


#endif