#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP
#include <SDL2/SDL.h>
#include "../AssetManager/AssetManager.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

class RenderSystem : public System {
    public:
        RenderSystem() {
            RequireComponent<TransformComponent>();
            RequireComponent<SpriteComponent>();
        }
        void Update(SDL_Renderer* renderer, std::unique_ptr<AssetManager>& AssetManager) {
            std::vector<Entity> entities = GetSystemEntities();
            
            size_t startIndex = 0;

            if (!entities.empty()) {
                const auto firstEntity = entities[0];
                if (firstEntity.HasComponent<SpriteComponent>()) {
                    const auto sprite = firstEntity.GetComponent<SpriteComponent>();
                    if (sprite.textureId.find("background") != std::string::npos) {
                        startIndex = 1;  // Saltar el primer elemento
                    }
                }
            }

            for (size_t i = startIndex; i < entities.size(); ++i) {
                const auto entity = entities[i];
                const auto transform = entity.GetComponent<TransformComponent>();
                const auto sprite = entity.GetComponent<SpriteComponent>();

                if (!sprite.active) {
                    continue;
                }

                SDL_Rect srcRect = sprite.srcRect;
                SDL_Rect dstRect = {
                    static_cast<int>(transform.position.x),
                    static_cast<int>(transform.position.y),
                    static_cast<int>(sprite.width * transform.scale.x),
                    static_cast<int>(sprite.height * transform.scale.y)
                };

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


        void UpdateBackground(SDL_Renderer* renderer, std::unique_ptr<AssetManager>& AssetManager) {
            auto& registry = Game::GetInstance().registry;
            auto entities = registry->GetEntitiesFromSystem<RenderSystem>();

            for (auto entity : entities) {
                if (!entity.HasComponent<TransformComponent>()) {
                    continue;
                }
                const auto transform = entity.GetComponent<TransformComponent>();
                const auto sprite = entity.GetComponent<SpriteComponent>();
                if (!sprite.active || sprite.textureId.find("background") == std::string::npos) {
                    continue;
                }

                SDL_Rect srcRect = sprite.srcRect;
                SDL_Rect dstRect = {
                    static_cast<int>(transform.position.x),
                    static_cast<int>(transform.position.y),
                    static_cast<int>(sprite.width * transform.scale.x),
                    static_cast<int>(sprite.height * transform.scale.y)
                };
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
#endif