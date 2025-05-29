#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <SDL2/SDL.h>
#include "../AssetManager/AssetManager.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @brief System responsible for rendering entities to the screen
 * 
 * Handles the drawing of all visible entities with sprite components,
 * including special handling for background rendering.
 */
class RenderSystem : public System {
public:
    /**
     * @brief Construct a new Render System object
     * 
     * Requires entities to have both TransformComponent and SpriteComponent
     */
    RenderSystem() {
        RequireComponent<TransformComponent>();
        RequireComponent<SpriteComponent>();
    }

    /**
     * @brief Render all visible entities (excluding background if it's first)
     * @param renderer SDL renderer to draw to
     * @param AssetManager Asset manager for texture access
     */
    void Update(SDL_Renderer* renderer, std::unique_ptr<AssetManager>& AssetManager) {
        std::vector<Entity> entities = GetSystemEntities();
        
        size_t startIndex = 0;

        // Special case: skip background if it's the first entity
        if (!entities.empty()) {
            const auto firstEntity = entities[0];
            if (firstEntity.HasComponent<SpriteComponent>()) {
                const auto sprite = firstEntity.GetComponent<SpriteComponent>();
                if (sprite.textureId.find("background") != std::string::npos) {
                    startIndex = 1;  // Skip first element (background)
                }
            }
        }

        // Render all entities starting from startIndex
        for (size_t i = startIndex; i < entities.size(); ++i) {
            const auto entity = entities[i];
            const auto transform = entity.GetComponent<TransformComponent>();
            const auto sprite = entity.GetComponent<SpriteComponent>();

            // Skip inactive sprites
            if (!sprite.active) {
                continue;
            }

            // Prepare source and destination rectangles
            SDL_Rect srcRect = sprite.srcRect;
            SDL_Rect dstRect = {
                static_cast<int>(transform.position.x),
                static_cast<int>(transform.position.y),
                static_cast<int>(sprite.width * transform.scale.x),
                static_cast<int>(sprite.height * transform.scale.y)
            };

            // Render with optional flip and rotation
            SDL_RenderCopyEx(
                renderer,
                AssetManager->GetTexture(sprite.textureId),
                &srcRect,
                &dstRect,
                transform.rotation,
                NULL,
                sprite.flip
            );
        }
    }

    /**
     * @brief Render only background entities
     * @param renderer SDL renderer to draw to
     * @param AssetManager Asset manager for texture access
     */
    void UpdateBackground(SDL_Renderer* renderer, std::unique_ptr<AssetManager>& AssetManager) {
        auto& registry = Game::GetInstance().registry;
        auto entities = registry->GetEntitiesFromSystem<RenderSystem>();

        for (auto entity : entities) {
            if (!entity.HasComponent<TransformComponent>()) {
                continue;
            }
            const auto transform = entity.GetComponent<TransformComponent>();
            const auto sprite = entity.GetComponent<SpriteComponent>();
            
            // Only render active background sprites
            if (!sprite.active || sprite.textureId.find("background") == std::string::npos) {
                continue;
            }

            // Prepare source and destination rectangles
            SDL_Rect srcRect = sprite.srcRect;
            SDL_Rect dstRect = {
                static_cast<int>(transform.position.x),
                static_cast<int>(transform.position.y),
                static_cast<int>(sprite.width * transform.scale.x),
                static_cast<int>(sprite.height * transform.scale.y)
            };
            
            // Render with optional flip and rotation
            SDL_RenderCopyEx(
                renderer,
                AssetManager->GetTexture(sprite.textureId),
                &srcRect,
                &dstRect,
                transform.rotation,
                NULL,
                sprite.flip
            );
        }
    }
};

#endif // RENDERSYSTEM_HPP