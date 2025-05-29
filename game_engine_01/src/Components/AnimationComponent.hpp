#ifndef ANIMATIONCOMPONENT_HPP
#define ANIMATIONCOMPONENT_HPP

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

/**
 * @struct AnimationComponent
 * @brief Component for handling sprite animations in the ECS.
 */
struct AnimationComponent {
    /** @brief Total number of frames in the animation. */
    int numFrames;

    /** @brief Current frame of the animation. */
    int currentFrame;

    /** @brief Speed at which frames are updated (in milliseconds). */
    int frameSpeedRate;

    /** @brief Indicates whether the animation should loop. */
    bool isLoop;

    /** @brief Time when the animation started, in milliseconds. */
    int startTime;

    /**
     * @brief Constructs an AnimationComponent with specified parameters.
     * @param numFrames Total number of frames in the animation (default: 1).
     * @param frameSpeedRate Speed of frame updates in milliseconds (default: 1).
     * @param isLoop Whether the animation should loop (default: true).
     */
    AnimationComponent(int numFrames = 1, int frameSpeedRate = 1, bool isLoop = true) {
        this->numFrames = numFrames;
        this->currentFrame = 1;
        this->frameSpeedRate = frameSpeedRate;
        this->isLoop = isLoop;
        this->startTime = SDL_GetTicks();
    }
};

#endif