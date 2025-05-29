#ifndef SCRIPT_COMPONENT_HPP
#define SCRIPT_COMPONENT_HPP

#include <sol/sol.hpp>

/**
 * @struct ScriptComponent
 * @brief Component for attaching Lua script functions to an entity in the ECS.
 */
struct ScriptComponent {
    /** @brief Lua function to be called during the update phase. */
    sol::function update;

    /** @brief Lua function to be called when the entity is clicked. */
    sol::function onClick;

    /**
     * @brief Constructs a ScriptComponent with specified Lua functions.
     * @param update Lua function for the update phase (default: nil).
     * @param onClick Lua function for click events (default: nil).
     */
    ScriptComponent(sol::function update = sol::lua_nil, 
                    sol::function onClick = sol::lua_nil) {
        this->update = update;
        this->onClick = onClick;
    }
};

#endif // SCRIPT_COMPONENT_HPP