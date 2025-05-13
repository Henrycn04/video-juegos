#ifndef SCRIPt_SYSTEM_HPP
#define SCRIPt_SYSTEM_HPP

#include <memory>
#include <sol/sol.hpp>
#include "../Binding/LuaBinding.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../ECS/ECS.hpp"

class ScriptSystem : public System {
public:
    ScriptSystem() {
        RequireComponent<ScriptComponent>();
    }
    void CreateLuaBinding(sol::state& lua) {
        lua.new_usertype<Entity>("entity");
        lua.set_function("is_action_activated", IsActionActivated);
        lua.set_function("set_velocity", SetVelocity);
        lua.set_function("go_to_scene", GoToScene);

        lua.set_function("is_mouse_button_down", IsMouseButtonDown);

        lua.set_function("push_draw_point", PushDrawPoint);

        lua.set_function("get_mouse_position", GetMousePosition);

    }
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
