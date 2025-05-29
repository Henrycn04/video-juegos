#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP

#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/ProjectileComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Game/Game.hpp"

/**
 * @brief System that handles entity movement and screen boundary constraints
 * 
 * Updates entity positions based on velocity and ensures they stay within
 * game boundaries. Also manages sprite flipping based on movement direction.
 */
class MovementSystem : public System {
public:
    /**
     * @brief Construct a new Movement System object
     * 
     * Requires entities to have:
     * - RigidBodyComponent
     * - TransformComponent
     * - SpriteComponent
     */
    MovementSystem() {
        RequireComponent<RigidBodyComponent>();
        RequireComponent<TransformComponent>();
        RequireComponent<SpriteComponent>();
    }

    /**
     * @brief Update entity positions and handle boundary collisions
     * @param dt Delta time since last frame (in seconds)
     */
    void Update(double dt) {
        auto& game = Game::GetInstance();

        for (auto entity : GetSystemEntities()) {
            const auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
            auto& transform = entity.GetComponent<TransformComponent>();
            auto& sprite = entity.GetComponent<SpriteComponent>();
            
            // Skip inactive sprites
            if (!sprite.active) {
                continue;
            }

            // Update position based on velocity and delta time
            transform.position.x += rigidBody.velocity.x * dt;
            transform.position.y += rigidBody.velocity.y * dt;
            
            bool crash = false;
            
            // X-axis boundary checks (with sprite width consideration)
            if (transform.position.x < 0) {
                transform.position.x = 0;
                crash = true;
            } else if (transform.position.x > game.windowWidth - (sprite.width * transform.scale.x)) {
                transform.position.x = game.windowWidth - (sprite.width * transform.scale.x);
                crash = true;
            }

            // Y-axis boundary checks (with sprite height consideration)
            if (transform.position.y < 175) {  // Top boundary
                transform.position.y = 175;
                crash = true;
            } else if (transform.position.y > game.windowHeight - (sprite.height * transform.scale.y) - 25) {  // Bottom boundary
                transform.position.y = game.windowHeight - (sprite.height * transform.scale.y) - 25;
                crash = true;
            }
            
            // Update sprite orientation based on horizontal velocity
            if (rigidBody.velocity.x < 0) {
                sprite.flip = SDL_FLIP_HORIZONTAL;
            } else if (rigidBody.velocity.x > 0) {
                sprite.flip = SDL_FLIP_NONE;
            }
            
            // Special handling for projectiles
            if (entity.HasComponent<ProjectileComponent>()) {
                sprite.flip = SDL_FLIP_NONE;
            }
            
            // Destroy projectiles that hit boundaries
            if (entity.HasComponent<ProjectileComponent>() && crash) {
                sprite.flip = SDL_FLIP_NONE;
                entity.Kill();
            }
        }
    }
};

#endif // MOVEMENTSYSTEM_HPP