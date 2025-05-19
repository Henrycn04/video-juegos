enemy_velocity = 150
fixed_enemy_velocity = math.sqrt((enemy_velocity * enemy_velocity) / 2)

function update()
    local player_x, player_y = get_position_player_position()

    -- Posición del enemigo
    local enemy_x, enemy_y = get_position(this)

    -- Vector hacia el jugador
    local dir_x = player_x - enemy_x
    local dir_y = player_y - enemy_y

    -- Calcular distancia al jugador
    local distance = math.sqrt(dir_x * dir_x + dir_y * dir_y)

    if distance < 80 then
        -- Si está muy cerca, atacar
        set_velocity(this, 0, 0)
        attack_ranger()
    elseif distance >= 80 then
        -- Si está lejos, moverse hacia el jugador
        local vel_x = (dir_x / distance) * enemy_velocity
        local vel_y = (dir_y / distance) * enemy_velocity
        set_velocity(this, vel_x, vel_y)
    else
        set_velocity(this, 0, 0)
    end
end