#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include <SDL2/SDL.h>

/**
 * @brief System that handles sprite animation
 * 
 * Updates animation frames for entities with both AnimationComponent
 * and SpriteComponent based on elapsed time and animation parameters.
 */
class AnimationSystem : public System {
public:
    /**
     * @brief Construct a new Animation System object
     * 
     * Requires entities to have both AnimationComponent and SpriteComponent
     */
    AnimationSystem() {
        RequireComponent<AnimationComponent>();
        RequireComponent<SpriteComponent>();
    }

    /**
     * @brief Update all animated entities
     * 
     * Calculates current animation frame based on:
     * - Time elapsed since animation started
     * - Frame speed rate
     * - Total number of frames
     * Updates sprite source rectangle to show current frame
     */
    void Update() {
        for (auto entity : GetSystemEntities()) {
            auto& animation = entity.GetComponent<AnimationComponent>();
            auto& sprite = entity.GetComponent<SpriteComponent>();

            // Calculate current frame based on elapsed time and animation speed
            animation.currentFrame = ((SDL_GetTicks() - animation.startTime) * 
                                    animation.frameSpeedRate / 1000) % 
                                    animation.numFrames;
            
            // Update sprite source rectangle to show current frame
            sprite.srcRect.x = animation.currentFrame * sprite.width;
        }
    }
};

#endif // ANIMATIONSYSTEM_HPP