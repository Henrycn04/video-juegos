#ifndef RENDERTEXTSYSTEM_HPP
#define RENDERTEXTSYSTEM_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include "../AssetManager/AssetManager.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/DamageChargeComponent.hpp"
#include "../Components/SprintChargeComponent.hpp"
#include "../Components/SlowChargeComponent.hpp"

#include "../ECS/ECS.hpp"

class RenderTextSystem : public System {
    public:
    RenderTextSystem() {
        RequireComponent<TextComponent>();
        RequireComponent<TransformComponent>();
    }

    void Update(SDL_Renderer* renderer, std::unique_ptr<AssetManager>& assetManager) {
        for (auto entity : GetSystemEntities()) {
            auto& text = entity.GetComponent<TextComponent>();
            auto& transform = entity.GetComponent<TransformComponent>();
            if (entity.HasComponent<HealthComponent>() ) {
                const auto sprite = entity.GetComponent<SpriteComponent>();
                if (!sprite.active) {
                    continue;
                }

                text.text = std::to_string(entity.GetComponent<HealthComponent>().health);
                SDL_Surface* surface = TTF_RenderText_Blended(assetManager->GetFont(text.fontId), text.text.c_str(), text.color);
                text.width = surface->w;
                text.height = surface->h;
                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_FreeSurface(surface);

                SDL_Rect dstrect = {
                    static_cast<int>(transform.position.x),
                    static_cast<int>(transform.position.y - 20),
                    text.width * static_cast<int>(transform.scale.x) / 2,
                    text.height * static_cast<int>(transform.scale.y) / 2
                };

                SDL_RenderCopy(renderer, texture, NULL, &dstrect);
                SDL_DestroyTexture(texture);
            } else if (entity.HasComponent<DamageChargeComponent>() || entity.HasComponent<SprintChargeComponent>() || entity.HasComponent<SlowChargeComponent>() ) {
                if (entity.HasComponent<DamageChargeComponent>()) {
                    text.text = entity.GetComponent<DamageChargeComponent>().chargeDisplay;
                } else if (entity.HasComponent<SprintChargeComponent>()) {
                    text.text = entity.GetComponent<SprintChargeComponent>().chargeDisplay;
                } else if (entity.HasComponent<SlowChargeComponent>()) {
                    text.text = entity.GetComponent<SlowChargeComponent>().chargeDisplay;
                }
                SDL_Surface* surface = TTF_RenderText_Blended(assetManager->GetFont(text.fontId), text.text.c_str(), text.color);
                text.width = surface->w;
                text.height = surface->h;
                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_FreeSurface(surface);

                SDL_Rect dstrect = {
                    static_cast<int>(transform.position.x),
                    static_cast<int>(transform.position.y - 20),
                    text.width * static_cast<int>(transform.scale.x) / 2,
                    text.height * static_cast<int>(transform.scale.y) / 2
                };

                SDL_RenderCopy(renderer, texture, NULL, &dstrect);
                SDL_DestroyTexture(texture);
            }
            else {
                SDL_Surface* surface = TTF_RenderText_Blended(assetManager->GetFont(text.fontId), text.text.c_str(), text.color);
                text.width = surface->w;
                text.height = surface->h;
                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_FreeSurface(surface);

                SDL_Rect dstrect = {
                    static_cast<int>(transform.position.x),
                    static_cast<int>(transform.position.y),
                    text.width * static_cast<int>(transform.scale.x),
                    text.height * static_cast<int>(transform.scale.y)
                };

                SDL_RenderCopy(renderer, texture, NULL, &dstrect);
                SDL_DestroyTexture(texture);
            }
        }
    }
};
#endif // RENDERTEXTSYSTEM_HPP