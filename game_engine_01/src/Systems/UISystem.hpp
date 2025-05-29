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

/**
 * @class UISystem
 * @brief System for handling UI interactions in the ECS framework.
 *
 * Manages clickable UI elements and handles click events by checking
 * collision between click positions and UI elements.
 */
class UISystem : public System {
    public:
        /**
         * @brief Constructs a UISystem and requires necessary components.
         *
         * Requires entities to have ClickableComponent, TransformComponent,
         * and TextComponent to be processed by this system.
         */
        UISystem() {
            RequireComponent<ClickableComponent>();
            RequireComponent<TransformComponent>();
            RequireComponent<TextComponent>();
        };

        /**
         * @brief Subscribes the system to click events.
         * @param eventManager Reference to the EventManager for event subscription.
         *
         * Registers the OnClickEvent method as a callback for ClickEvents.
         */
        void SubscribeToClickEvent(std::unique_ptr<EventManager>& eventManager) {
            eventManager->SubscribeToEvent<UISystem, ClickEvent>(this, &UISystem::OnClickEvent);
        };

        /**
         * @brief Handles click events on UI elements.
         * @param e Reference to the ClickEvent containing click coordinates.
         *
         * Checks if click coordinates are within any UI element's bounds and
         * triggers the associated onClick Lua callback if it exists.
         */
        void OnClickEvent(ClickEvent& e) {
            for (auto entity : GetSystemEntities()) {
                auto& transform = entity.GetComponent<TransformComponent>();
                auto& text = entity.GetComponent<TextComponent>();
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