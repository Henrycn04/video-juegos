
scene = {
    -- Tabla de imagenes
    sprites = {
        [0] = 
        {assetId = "enemy_alan", file_path = "./assets/images/enemy_alan.png"},
        {assetId = "player_dino", file_path = "./assets/images/dino.png"}
    },
    -- Tabla de fuentes
    fonts = {
        [0] = {fontId = "press_start_24", filePath = "./assets/fonts/press_start_2p.ttf", fontSize = 24},

    },
    -- Tabla de acciones y teclas
    keys = {
        [0] = {name = "move_left", key = 97},
        {name = "move_right", key = 100},
        {name = "move_up", key = 119},
        {name = "move_down", key = 115},
        {name = "jump", key = 32},
        

    },
    -- Tabla de acciones y botones del raton
    buttons = {
        [0] = {name = "mouse_left_button", button = 1},

    },
    -- Tabla de entidades
    entities = {
        [0] =
        -- Player
        {
            components = { -- Jugador
                animation = {
                    num_frames = 5,
                    frame_speed_rate = 10,
                    loop = true,
                },
                circle_collider = {
                    radius = 12,
                    width = 24,
                    height = 24
                },
                rigidbody = {
                    velocity = {
                        x = 0,
                        y = 0
                    },
                },
                script = {
                    path = "./assets/scripts/player.lua"
                },
                sprite = {
                    assetId = "player_dino",
                    width = 24,
                    height = 24,
                    src_rect = {
                        x = 24,
                        y = 0,
                    },
                },
                transform = {
                    position = {
                        x = 400,
                        y = 300
                    },
                    scale = {
                        x = 2.0,
                        y = 2.0
                    },
                    rotation = 0.0
                },
            }
        },
        {
            components = { -- Alan 1
                animation = {
                    num_frames = 6,
                    frame_speed_rate = 10,
                    loop = true,
                },
                circle_collider = {
                    radius = 16,
                    width = 16,
                    height = 16
                },
                rigidbody = {
                    velocity = {
                        x = 25,
                        y = 0
                    },
                },
                sprite = {
                    assetId = "enemy_alan",
                    width = 16,
                    height = 16,
                    src_rect = {
                        x = 16,
                        y = 0,
                    },
                },
                transform = {
                    position = {
                        x = 200.0,
                        y = 100.0
                    },
                    scale = {
                        x = 4.0,
                        y = 3.0
                    },
                    rotation = 0.0
                },
            }
        },
        {
            components = { -- Alan 2
                animation = {
                    num_frames = 6,
                    frame_speed_rate = 10,
                    loop = true,
                },
                circle_collider = {
                    radius = 16,
                    width = 16,
                    height = 16
                },
                rigidbody = {
                    velocity = {
                        x = -25,
                        y = 0
                    },
                },
                sprite = {
                    assetId = "enemy_alan",
                    width = 16,
                    height = 16,
                    src_rect = {
                        x = 16,
                        y = 0,
                    },
                },
                transform = {
                    position = {
                        x = 450.0,
                        y = 100.0
                    },
                    scale = {
                        x = 4.0,
                        y = 3.0
                    },
                    rotation = 0.0
                },
            },


        },
        {
            components = {
                clickable = {

                },
                text = {
                    text = "Score: 100",
                    fontId = "press_start_24",
                    r = 150,
                    g = 0,
                    b = 150,
                    a = 255,

                },
                transform = {
                    position = {
                        x = 500,
                        y = 50
                    },
                    scale = {
                        x = 1.0,
                        y = 1.0
                    },
                    rotation = 0.0
                },
            }
        }
    }
}