#ifndef UISYSTEM_HPP
#define UISYSTEM_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <memory>
#include <iostream>
#include <string>

#include "../Components/ClickableComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/TextComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/ClickEvent.hpp"

class UISystem : public System {
    public:
        UISystem() {
            RequireComponent<ClickableComponent>();
            RequireComponent<TransformComponent>();
            RequireComponent<TextComponent>();
        };
        void SubscribeToClickEvent(std::unique_ptr<EventManager>& eventManager) {
            eventManager->SubscribeToEvent<UISystem, ClickEvent>(this, &UISystem::OnClickEvent);
        };
        void OnClickEvent(ClickEvent& e) {
            for (auto entity : GetSystemEntities()) {
                auto& transform = entity.GetComponent<TransformComponent>();
                auto& text = entity.GetComponent<TextComponent>();
std::cout << "[UISystem] Clicked on entity with ID: " << entity.GetId() << std::endl;
                if (transform.position.x < e.x && e.x < transform.position.x + text.width &&
                    transform.position.y < e.y && e.y < transform.position.y + text.height) {
                    
                    if (entity.HasComponent<ClickableComponent>()) {
                        const auto& script = entity.GetComponent<ScriptComponent>();
                        if (script.onClick != sol::lua_nil) {
                            script.onClick();
                        }

                    }
                }
            }
        };
};

#endif // UISYSTEM_HPP