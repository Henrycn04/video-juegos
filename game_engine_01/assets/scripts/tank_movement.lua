enemy_velocity = 85

function update()
    local player_x, player_y = get_player_position()
    local enemy_x, enemy_y = get_enemy_position(this)
    
    local dir_x = player_x - enemy_x
    local dir_y = player_y - enemy_y
    local distance = math.sqrt(dir_x * dir_x + dir_y * dir_y)
    
    if distance < 20 then
        set_velocity(this, 0, 0)
        attack_melee(this)
        return
    end
    
    -- Base chase velocity
    local vel_x = (dir_x / distance) * enemy_velocity
    local vel_y = (dir_y / distance) * enemy_velocity
    
    -- Simple separation: check all enemies and push away from close ones
    local all_enemies = get_all_enemies()
    for i, enemy in ipairs(all_enemies) do
        if enemy ~= this then
            local other_x, other_y = get_enemy_position_by_id(enemy)
            if other_x and other_y then
                local dx = enemy_x - other_x
                local dy = enemy_y - other_y
                local dist = math.sqrt(dx * dx + dy * dy)
                
                -- If too close, push away (reduced values for 32x32 sprites)
                if dist < 40 then  -- Slightly larger detection
                    local push_force = 40 * (40 - dist) / 40  -- Much smaller force
                    
                    if dist < 1 then
                        -- Handle perfect overlap with more stable angles
                        local angle = (i * 1.2) + math.random() * 0.6  -- Less random variation
                        vel_x = vel_x + math.cos(angle) * push_force
                        vel_y = vel_y + math.sin(angle) * push_force
                    else
                        -- Push away from other enemy (reduced impact)
                        vel_x = vel_x + (dx / dist) * push_force * 0.3  -- Even less impact
                        vel_y = vel_y + (dy / dist) * push_force * 0.3
                    end
                end
            end
        end
    end
    
    set_velocity(this, vel_x, vel_y)
end
