
scene = {
    background = {
        [0] = {assetId = "background04", file_path = "./assets/images/background04.png"},
    },
    -- Tabla de imagenes
    sprites = {
        [0] = 
        {assetId = "tank01", file_path = "./assets/images/tank01.png"},
        {assetId = "player_dino", file_path = "./assets/images/player.png"},
        {assetId = "ranger01", file_path = "./assets/images/ranger01.png"},
        {assetId = "melee02", file_path = "./assets/images/melee02.png"},
        {assetId = "arrow01", file_path = "./assets/images/arrow01.png"},
        {assetId = "pow01", file_path = "./assets/images/pow01.png"},
        {assetId = "pow02", file_path = "./assets/images/pow02.png"},
        {assetId = "pow03", file_path = "./assets/images/pow03.png"},
        {assetId = "pow04", file_path = "./assets/images/pow04.png"},
        {assetId = "pow05", file_path = "./assets/images/pow05.png"},
        {assetId = "pow06", file_path = "./assets/images/pow06.png"},

    },
    -- Tabla de fuentes
    fonts = {
        [0] = {fontId = "press_start_24", filePath = "./assets/fonts/press_start_2p.ttf", fontSize = 24},
        {fontId = "press_start_32", filePath = "./assets/fonts/press_start_2p.ttf", fontSize = 32},
                {fontId = "press_start_50", filePath = "./assets/fonts/press_start_2p.ttf", fontSize = 50},

    },

    sounds = {
        [0] = {soundId = "game_music", filePath = "./assets/sounds/game_music.mp3"},
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
                    assetId = "background04",
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
            components = { -- sonido
                sound = {
                    soundId = "game_music",
                    volume = 20,
                    loops = -1,
                    autoPlay = true,
                    active = true,
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
                    health = 30,
                    maxHealth = 30,
                    isPlayer = false,
                    damage = 10,
                    attack_timeout = 1.0,
                },
                enemy = {
                    amountToSpawn = 3,
                    totalAmount = 10,
                    points = 20
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
                    health = 40,
                    maxHealth = 40,
                    isPlayer = false,
                    damage = 15,
                    attack_timeout = 1.0,
                },
                enemy = {
                    amountToSpawn = 4,
                    totalAmount = 12,
                    points = 15
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
                    health = 80,
                    maxHealth = 80,
                    isPlayer = false,
                    damage = 20,
                    attack_timeout = 1.0,
                },
                enemy = {
                    amountToSpawn = 2,
                    totalAmount = 6,
                    points = 10
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
        {   components = { -- Flecha
                animation = {
                    num_frames = 30,
                    frame_speed_rate = 30,
                    loop = true,
                },
                circle_collider = {
                    radius = 8,
                    width = 16,
                    height = 5
                },
                rigidbody = {
                    velocity = {
                        x = 0,
                        y = 0
                    },
                },
                
                projectile = {
                },
                enemy = {
                    amountToSpawn = 0,
                    totalAmount = 0,
                    points = 0
                },
                sprite = {
                    assetId = "arrow01",
                    width = 16,
                    height = 5,
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
            },


        },
        -- Crear una entidad de proyectil que usen los rangers
                { -- Texto de puntuacion
            components = {
                identifier = {
                    id = 0,
                    name = "puntuacion"
                },
                clickable = {
                },
                text = {
                    text = "",
                    fontId = "press_start_50",
                    r = 34,
                    g = 34,
                    b = 34,
                    a = 255,

                },
                transform = {
                    position = {
                        x = 495,
                        y = 100
                    },
                    scale = {
                        x = 1.0,
                        y = 1.0
                    },
                    rotation = 0.0
                },
            }
        },
        { -- Texto de puntuacion
            components = {
                identifier = {
                    id = 0,
                    name = "puntuacion"
                },
                clickable = {
                },
                text = {
                    text = "",
                    fontId = "press_start_50",
                    r = 255,
                    g = 255,
                    b = 255,
                    a = 255,

                },
                transform = {
                    position = {
                        x = 500,
                        y = 100
                    },
                    scale = {
                        x = 1.0,
                        y = 1.0
                    },
                    rotation = 0.0
                },
            }
        },
        { -- Carga de danno off
            components = {
                sprite = {
                    assetId = "pow02",
                    width = 75,
                    height = 135,
                    src_rect = {
                        x = 0,
                        y = 0,
                    },
                    active = true,
                },
                transform = {
                    position = {
                        x = 50,
                        y = 40
                    },
                    scale = {
                        x = 1,
                        y = 1
                    },
                    rotation = 0.0
                },
            }
        },
        { -- Carga de danno on
            components = {
                identifier = {
                    id = 0,
                    name = "pow01"
                },
                sprite = {
                    assetId = "pow01",
                    width = 75,
                    height = 135,
                    src_rect = {
                        x = 0,
                        y = 0,
                    },
                    active = false,
                },
                damageCharge = {
                    totalCharge = 100,
                    initialCharge = 100,
                },
                text = {
                    text = "",
                    fontId = "press_start_32",
                    r = 255,
                    g = 0,
                    b = 0,
                    a = 255,

                },
                transform = {
                    position = {
                        x = 50,
                        y = 40
                    },
                    scale = {
                        x = 1,
                        y = 1
                    },
                    rotation = 0.0
                },
            }
        },
        { -- Carga de rapidez off
            components = {
                sprite = {
                    assetId = "pow04",
                    width = 75,
                    height = 135,
                    src_rect = {
                        x = 0,
                        y = 0,
                    },
                    active = true,
                },

                transform = {
                    position = {
                        x = 175,
                        y = 40
                    },
                    scale = {
                        x = 1,
                        y = 1
                    },
                    rotation = 0.0
                },
            }
        },
        { -- Carga de rapidez on
            components = {
                identifier = {
                    id = 0,
                    name = "pow03"
                },
                sprite = {
                    assetId = "pow03",
                    width = 75,
                    height = 135,
                    src_rect = {
                        x = 0,
                        y = 0,
                    },
                    active = false,
                },
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
                        y = 40
                    },
                    scale = {
                        x = 1,
                        y = 1
                    },
                    rotation = 0.0
                },
            }
        },
        { -- Carga de slow off
            components = {
                sprite = {
                    assetId = "pow06",
                    width = 75,
                    height = 135,
                    src_rect = {
                        x = 0,
                        y = 0,
                    },
                    active = true,
                },

                transform = {
                    position = {
                        x = 300,
                        y = 40
                    },
                    scale = {
                        x = 1,
                        y = 1
                    },
                    rotation = 0.0
                },
            }
        },
        { -- Carga de slow on
            components = {
                identifier = {
                    id = 0,
                    name = "pow05"
                },
                sprite = {
                    assetId = "pow05",
                    width = 75,
                    height = 135,
                    src_rect = {
                        x = 0,
                        y = 0,
                    },
                    active = false,
                },
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
                        y = 40
                    },
                    scale = {
                        x = 1,
                        y = 1
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
                        x = 0,
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