#ifndef DRAWSYSTEM_HPP
#define DRAWSYSTEM_HPP

#include <SDL2/SDL.h>
#include <vector>
#include "../ECS/ECS.hpp"
#include "../Components/DrawableComponent.hpp"
#include <chrono>
#include "../Game/Game.hpp"
#include "../Systems/ChargeManageSystem.hpp"

/**
 * @brief System responsible for rendering drawable components
 * 
 * Handles the drawing of colored points and manages their lifetime.
 */
class DrawSystem : public System {
public:
    /**
     * @brief Construct a new Draw System object
     * 
     * Requires entities to have a DrawableComponent
     */
    DrawSystem() {
        RequireComponent<DrawableComponent>();
    }

    /**
     * @brief Update and render all drawable components
     * @param renderer SDL renderer used for drawing
     */
    void Update(SDL_Renderer* renderer) {
        // Process each entity with drawable component
        for (auto entity : GetSystemEntities()) {
            auto& drawable = entity.GetComponent<DrawableComponent>();
            
            // Process each color channel
            for (size_t i = 0; i < drawable.colorPoints.size(); ++i) {
                // Set color based on channel index
                SDL_Color color;
                switch (i) {
                    case 0: color = {255, 0, 0, 255}; break;   // Red
                    case 1: color = {0, 0, 255, 255}; break;   // Blue
                    case 2: color = {0, 255, 0, 255}; break;   // Green
                    default: color = {255, 255, 255, 255}; break; // White
                }

                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                
                // Remove points older than 4 seconds when game is not paused
                if (!Game::GetInstance().isPaused) {
                    auto now = std::chrono::steady_clock::now();
                    for (auto it = drawable.colorPoints[i].begin(); it != drawable.colorPoints[i].end(); ) {
                        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - it->second);
                        if (duration.count() > 4) {
                            it = drawable.colorPoints[i].erase(it); // Remove expired point
                        } else {
                            ++it;
                        }
                    }
                }

                // Draw remaining points in gameplay area (below y=175)
                for (const auto& point : drawable.colorPoints[i]) {
                    if (point.first.y > 175) {
                        int size = 10; // Stroke size
                        SDL_Rect drawRect = {
                            static_cast<int>(point.first.x) - size / 2,
                            static_cast<int>(point.first.y) - size / 2,
                            size,
                            size
                        };
                        SDL_RenderFillRect(renderer, &drawRect);
                    }
                }
            }
        }
    }
};

#endif // DRAWSYSTEM_HPP