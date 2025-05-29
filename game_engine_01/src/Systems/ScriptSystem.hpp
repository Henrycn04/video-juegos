#ifndef SCRIPt_SYSTEM_HPP
#define SCRIPt_SYSTEM_HPP

#include <memory>
#include <sol/sol.hpp>
#include "../Binding/LuaBinding.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @class ScriptSystem
 * @brief System for handling script components and Lua bindings.
 * 
 * This system manages entities with ScriptComponents and provides Lua bindings
 * for game functionality.
 */
class ScriptSystem : public System {
public:
    /**
     * @brief Constructs a ScriptSystem and requires ScriptComponent for entities.
     */
    ScriptSystem() {
        RequireComponent<ScriptComponent>();
    }

    /**
     * @brief Creates Lua bindings for game functions and types.
     * @param lua Reference to the Lua state to bind functions to.
     * 
     * Sets up various game-related functions in the Lua environment including:
     * - Input handling
     * - Entity manipulation
     * - Drawing functions
     * - Game state management
     */
    void CreateLuaBinding(sol::state& lua) {
        lua.script("math.randomseed(os.time())");
        lua.new_usertype<Entity>("entity");
        lua.set_function("is_action_activated", IsActionActivated);
        lua.set_function("set_velocity", SetVelocity);
        lua.set_function("go_to_scene", GoToScene);

        lua.set_function("is_mouse_button_down", IsMouseButtonDown);

        lua.set_function("push_draw_point", PushDrawPoint);

        lua.set_function("get_mouse_position", GetMousePosition);
        lua.set_function("get_player_position", GetPlayerPosition);
        lua.set_function("get_enemy_position", GetEnemyPosition);
        lua.set_function("attack_melee", AttackMelee);
        lua.set_function("get_all_enemies", GetAllEnemies);
        lua.set_function("get_enemy_position_by_id", GetEnemyPositionById);
        lua.set_function("attack_ranger", AttackRanger);
        lua.set_function("set_draw_index", CurrentDrawIndex);
        lua.set_function("set_level", SetLevel);
    }

    /**
     * @brief Updates all script components in the system.
     * @param lua Reference to the Lua state for script execution.
     * 
     * Iterates through all entities with ScriptComponents and calls their
     * update function if it exists.
     */
    void Update(sol::state& lua) {
        for (auto entity : GetSystemEntities()) {
            const auto& script = entity.GetComponent<ScriptComponent>();

            if (script.update != sol::lua_nil) {
                lua["this"] = entity;
                script.update();
            }
        }
    }
};

#endif // SCRIPt_SYSTEM_HPP