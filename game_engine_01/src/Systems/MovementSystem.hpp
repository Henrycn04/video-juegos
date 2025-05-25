#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/ProjectileComponent.hpp"

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
                
                if (!sprite.active) {
                    continue;
                }


                transform.position.x += rigidBody.velocity.x * dt;
                transform.position.y += rigidBody.velocity.y * dt;
                bool crash = false;
                // Clamp tomando en cuenta tamaño del sprite
                if (transform.position.x < 0) {
                    transform.position.x = 0;
                    crash = true;
                } else if (transform.position.x > game.windowWidth - (sprite.width * transform.scale.x)) {
                    transform.position.x = game.windowWidth - (sprite.width * transform.scale.x);
                    crash = true;

                }

                if (transform.position.y < 75) {
                    transform.position.y = 75;
                    crash = true;
                } else if (transform.position.y > game.windowHeight - (sprite.height * transform.scale.y)) {
                    transform.position.y = game.windowHeight - (sprite.height * transform.scale.y);
                    crash = true;
                }
                // Ajustar orientación horizontal del sprite según velocidad
                
                if (rigidBody.velocity.x < 0) {
                    sprite.flip = SDL_FLIP_HORIZONTAL;
                } else if (rigidBody.velocity.x > 0) {
                    sprite.flip = SDL_FLIP_NONE;
                }
                if (entity.HasComponent<ProjectileComponent>()) {
                    sprite.flip = SDL_FLIP_NONE;
                }
                if (entity.HasComponent<ProjectileComponent>() && crash) {
                    sprite.flip = SDL_FLIP_NONE;
                    entity.Kill();
                }

            }
        }

};


#endif