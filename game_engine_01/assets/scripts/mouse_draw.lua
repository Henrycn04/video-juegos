
function update()
    if is_action_activated("draw_red") then
        print("HOLAAAAAAAAAAAAAAAAAAAAAAAAA")
        current_draw_index = 0
    elseif is_action_activated("draw_blue") then
                print("HOLAAAAAAAAAAAAAAAAAAAAAAAAA")

        current_draw_index = 1
    elseif is_action_activated("draw_green") then
                print("HOLAAAAAAAAAAAAAAAAAAAAAAAAA")

        current_draw_index = 2
    end

    if is_mouse_button_down("mouse_left_button") then
        local x, y = get_mouse_position()
        print("HOLAAAAAAAAAAAAAAAAAAAAAAAAA: ", x, y)

        push_draw_point(this, current_draw_index, x, y)
    end
end