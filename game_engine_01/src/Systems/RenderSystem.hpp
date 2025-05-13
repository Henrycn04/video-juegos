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
            for (auto entity : GetSystemEntities()) {
                const auto transform = entity.GetComponent<TransformComponent>();
                const auto sprite = entity.GetComponent<SpriteComponent>();
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
                    SDL_FLIP_NONE
                );
                
            }

        }
};
#endif