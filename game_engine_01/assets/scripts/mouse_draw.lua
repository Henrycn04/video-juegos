
function update()
    if is_action_activated("draw_red") then
        current_draw_index = 0
        set_draw_index(this, current_draw_index)
    elseif is_action_activated("draw_blue") then
        current_draw_index = 1
        set_draw_index(this, current_draw_index)
    elseif is_action_activated("draw_green") then
        current_draw_index = 2
        set_draw_index(this, current_draw_index)
    end

    if is_mouse_button_down("mouse_left_button") then
        local x, y = get_mouse_position()
        
        push_draw_point(this, current_draw_index, x, y)
    end
end