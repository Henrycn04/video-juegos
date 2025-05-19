enemy_velocity = 100
fixed_enemy_velocity = math.sqrt((enemy_velocity * enemy_velocity) / 2)

function update()
    local player_x, player_y = get_player_position()

    local enemy_x, enemy_y = get_enemy_position(this)

    -- Desplazamiento aleatorio para evitar que todos apunten al mismo punto
    local offset_x = math.random(-20, 20)
    local offset_y = math.random(-20, 20)

    local target_x = player_x + offset_x
    local target_y = player_y + offset_y

    local dir_x = target_x - enemy_x - 50
    local dir_y = target_y - enemy_y 

    local distance = math.sqrt(dir_x * dir_x + dir_y * dir_y)

    if distance < 30 then
        set_velocity(this, 0, 0)
        attack_melee(this)
    elseif distance >= 30 then
        local vel_x = (dir_x / distance) * enemy_velocity
        local vel_y = (dir_y / distance) * enemy_velocity
        set_velocity(this, vel_x, vel_y)
    else
        set_velocity(this, 0, 0)
    end
end

