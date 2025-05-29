#ifndef DRAWABLE_COMPONENT_HPP
#define DRAWABLE_COMPONENT_HPP

#include <SDL2/SDL.h>
#include <vector>
#include <glm/vec2.hpp>
#include <chrono>

/**
 * @struct DrawableComponent
 * @brief Component for managing drawable elements with colored points and timestamps in the ECS.
 */
struct DrawableComponent {
    /** @brief Color used for rendering the drawable element. */
    SDL_Color color;

    /** @brief Vector of point lists for different colors (red, blue, green), each with position and timestamp. */
    std::vector<std::vector<std::pair<glm::vec2, std::chrono::steady_clock::time_point>>> colorPoints;

    /**
     * @brief Default constructor initializing with white color and three empty point lists.
     */
    DrawableComponent() {
        color = {255, 255, 255, 255}; // White
        colorPoints.resize(3); // Red, blue, green
    }

    /**
     * @brief Constructor initializing with a specified color and three empty point lists.
     * @param col The SDL_Color to set for the component.
     */
    DrawableComponent(SDL_Color col) {
        color = col;
        colorPoints.resize(3); // Red, blue, green
    }
};

#endif // DRAWABLE_COMPONENT_HPP