
scene = {
    background = {
        [0] = {assetId = "background1", file_path = "./assets/images/background1.jpg"},
    },
    -- Tabla de imagenes
    sprites = {
        [0] = 
        {assetId = "tank01", file_path = "./assets/images/tank01.png"},
        {assetId = "player_dino", file_path = "./assets/images/dino.png"},
        {assetId = "ranger01", file_path = "./assets/images/ranger01.png"},
        {assetId = "melee02", file_path = "./assets/images/melee02.png"},
    },
    -- Tabla de fuentes
    fonts = {
        [0] = {fontId = "press_start_24", filePath = "./assets/fonts/press_start_2p.ttf", fontSize = 24},
        {fontId = "press_start_32", filePath = "./assets/fonts/press_start_2p.ttf", fontSize = 32},


    },
    -- Tabla de acciones y teclas
    keys = {
        [0] = {name = "move_left", key = 97},
        {name = "move_right", key = 100},
        {name = "move_up", key = 119},
        {name = "move_down", key = 115},
        {name = "jump", key = 32},
        { name = "draw_red", key = 49 },   -- tecla 1
        { name = "draw_blue", key = 50 },  -- tecla 2
        { name = "draw_green", key = 51 },
        

    },
    -- Tabla de acciones y botones del raton
    buttons = {
        [0] = {name = "mouse_left_button", button = 1},

    },
    -- Tabla de entidades
    entities = {
        [0] =
            {
            components = {
                sprite = {
                    assetId = "background1",
                    width = 800,
                    height = 600,
                    src_rect = {
                        x = 0,
                        y = 0,
                    },
                    active = true,
                },
                transform = {
                    position = {
                        x = 0.0,
                        y = 0.0
                    },
                    scale = {
                        x = 1.0,
                        y = 1.0
                    },
                    rotation = 0.0
                },
            }
        },
        {
            components = {
                drawable = {
                },
                script = {
                    path = "./assets/scripts/mouse_draw.lua"
                },
            }

        },
        {
        components = { -- Enemigo plantilla ranger
                animation = {
                    num_frames = 6,
                    frame_speed_rate = 18,
                    loop = true,
                },
                circle_collider = {
                    radius = 10,
                    width = 22,
                    height = 20
                },
                health = {
                    health = 60,
                    maxHealth = 60,
                    isPlayer = false,
                    damage = 0,
                    attack_timeout = 1.0,
                },
                enemy = {
                    amountToSpawn = 1,
                    totalAmount = 1,
                },
                rigidbody = {
                    velocity = {
                        x = 0,
                        y = 0
                    },
                },
                script = {
                    path = "./assets/scripts/ranger_movement.lua"
                },
                sprite = {
                    assetId = "ranger01",
                    width = 22,
                    height = 20,
                    src_rect = {
                        x = 0,
                        y = 0,
                    },
                    active = false,
                },
                transform = { -- Generar en 0, luego se crean
                    position = {
                        x = 0.0,
                        y = 0.0
                    },
                    scale = {
                        x = 1,
                        y = 1
                    },
                    rotation = 0.0
                },
                effect_receiver = {
                },
                text = {
                    text = "",
                    fontId = "press_start_24",
                    r = 50,
                    g = 255,
                    b = 50,
                    a = 255,
                },
            },


        },
        {
        components = { -- Enemigo plantilla melee
                animation = {
                    num_frames = 7,
                    frame_speed_rate = 10,
                    loop = true,
                },
                circle_collider = {
                    radius = 13,
                    width = 28,
                    height = 29
                },
                health = {
                    health = 80,
                    maxHealth = 80,
                    isPlayer = false,
                    damage = 15,
                    attack_timeout = 1.0,
                },
                enemy = {
                    amountToSpawn = 1,
                    totalAmount = 1,
                },
                rigidbody = {
                    velocity = {
                        x = 0,
                        y = 0
                    },
                },
                script = {
                    path = "./assets/scripts/melee_movement.lua"
                },
                sprite = {
                    assetId = "melee02",
                    width = 28,
                    height = 29,
                    src_rect = {
                        x = 0,
                        y = 0,
                    },
                    active = false,
                },
                transform = { -- Generar en 0, luego se crean
                    position = {
                        x = 0.0,
                        y = 0.0
                    },
                    scale = {
                        x = 1,
                        y = 1
                    },
                    rotation = 0.0
                },
                effect_receiver = {
                },
                text = {
                    text = "",
                    fontId = "press_start_24",
                    r = 50,
                    g = 255,
                    b = 50,
                    a = 255,
                },
            },


        },
        {
        components = { -- Enemigo plantilla tanque
                animation = {
                    num_frames = 7,
                    frame_speed_rate = 10,
                    loop = true,
                },
                circle_collider = {
                    radius = 13,
                    width = 23,
                    height = 30
                },
                health = {
                    health = 40,
                    maxHealth = 40,
                    isPlayer = false,
                    damage = 10,
                    attack_timeout = 1.0,
                },
                enemy = {
                    amountToSpawn = 1,
                    totalAmount = 1,
                },
                rigidbody = {
                    velocity = {
                        x = 0,
                        y = 0
                    },
                },
                script = {
                    path = "./assets/scripts/tank_movement.lua"
                },
                sprite = {
                    assetId = "tank01",
                    width = 23,
                    height = 30,
                    src_rect = {
                        x = 0,
                        y = 0,
                    },
                    active = false,
                },
                transform = { -- Generar en 0, luego se crean
                    position = {
                        x = 0.0,
                        y = 0.0
                    },
                    scale = {
                        x = 1,
                        y = 1
                    },
                    rotation = 0.0
                },
                effect_receiver = {
                },
                text = {
                    text = "",
                    fontId = "press_start_24",
                    r = 50,
                    g = 255,
                    b = 50,
                    a = 255,
                },
            },


        },
        -- Crear una entidad de proyectil que usen los rangers
        { -- Texto de puntuacion
            components = {
                clickable = {
                },
                text = {
                    text = "Score: 100",
                    fontId = "press_start_24",
                    r = 50,
                    g = 255,
                    b = 50,
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
        },
        { -- Carga de danno
            components = {
                damageCharge = {
                    totalCharge = 100,
                    initialCharge = 100,
                },
                text = {
                    text = "D",
                    fontId = "press_start_32",
                    r = 255,
                    g = 0,
                    b = 0,
                    a = 255,

                },
                transform = {
                    position = {
                        x = 50,
                        y = 50
                    },
                    scale = {
                        x = 1.5,
                        y = 2
                    },
                    rotation = 0.0
                },
            }
        },
                { -- Carga de rapidez
            components = {
                sprintCharge = {
                    totalCharge = 100,
                    initialCharge = 100,
                },
                text = {
                    text = "R",
                    fontId = "press_start_32",
                    r = 0,
                    g = 0,
                    b = 255,
                    a = 255,

                },
                transform = {
                    position = {
                        x = 175,
                        y = 50
                    },
                    scale = {
                        x = 1.5,
                        y = 2
                    },
                    rotation = 0.0
                },
            }
        },
        { -- Carga de slow
            components = {
                slowCharge = {
                    totalCharge = 100,
                    initialCharge = 100,
                },
                text = {
                    text = "S",
                    fontId = "press_start_32",
                    r = 0,
                    g = 255,
                    b = 0,
                    a = 255,

                },
                transform = {
                    position = {
                        x = 300,
                        y = 50
                    },
                    scale = {
                        x = 1.5,
                        y = 2
                    },
                    rotation = 0.0
                },
            }
        },
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
                health = {
                    health = 100,
                    maxHealth = 100,
                    isPlayer = true,
                    damage = 10,
                    attack_timeout = 1.0,
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
                    active = true,
                },
                text = {
                    text = "",
                    fontId = "press_start_24",
                    r = 50,
                    g = 255,
                    b = 50,
                    a = 255,
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
                effect_receiver = {
                },
            }
        },     

    }
}