#ifndef DRAWABLE_COMPONENT_HPP
#define DRAWABLE_COMPONENT_HPP
#include <SDL2/SDL.h>
#include <vector>
#include <glm/vec2.hpp>
#include <chrono> // Para el manejo de tiempo

struct DrawableComponent {
    SDL_Color color;
    std::vector<std::vector<std::pair<glm::vec2, std::chrono::steady_clock::time_point>>> colorPoints; // ahora cada punto lleva un timestamp

    // Constructor por defecto
    DrawableComponent() {
        color = {255, 255, 255, 255}; // Blanco
        colorPoints.resize(3); // rojo, azul, verde
    }

    // Constructor con color
    DrawableComponent(SDL_Color col) {
        color = col;
        colorPoints.resize(3);
    }
};
#endif // DRAWABLE_COMPONENT_HPP