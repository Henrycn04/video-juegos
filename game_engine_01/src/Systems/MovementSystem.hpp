#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Game/Game.hpp"
class MovementSystem : public System {
    public:
        MovementSystem() {
            RequireComponent<RigidBodyComponent>();
            RequireComponent<TransformComponent>();
            RequireComponent<SpriteComponent>();

        }

        void Update(double dt) {
            auto& game = Game::GetInstance();

            for (auto entity : GetSystemEntities()) {
                const auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
                auto& transform = entity.GetComponent<TransformComponent>();
                auto& sprite = entity.GetComponent<SpriteComponent>();

                transform.position.x += rigidBody.velocity.x * dt;
                transform.position.y += rigidBody.velocity.y * dt;

                // Clamp tomando en cuenta tamaño del sprite
                if (transform.position.x < 0) {
                    transform.position.x = 0;
                } else if (transform.position.x > game.windowWidth - (sprite.width * transform.scale.x)) {
                    transform.position.x = game.windowWidth - (sprite.width * transform.scale.x);
                }

                if (transform.position.y < 75) {
                    transform.position.y = 75;
                } else if (transform.position.y > game.windowHeight - (sprite.height * transform.scale.y)) {
                    transform.position.y = game.windowHeight - (sprite.height * transform.scale.y);
                }
                // Ajustar orientación horizontal del sprite según velocidad
                if (rigidBody.velocity.x < 0) {
                    sprite.flip = SDL_FLIP_HORIZONTAL;
                } else if (rigidBody.velocity.x > 0) {
                    sprite.flip = SDL_FLIP_NONE;
                }

            }
        }

};


#endif