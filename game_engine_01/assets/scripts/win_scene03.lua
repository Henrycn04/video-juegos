
scene = {
    background = {
        [0] = {assetId = "background02", file_path = "./assets/images/background02.png"},

    },
    -- Tabla de imagenes
    sprites = {
    },
    -- Tabla de fuentes
    fonts = {
        [0] = {fontId = "press_start_24", filePath = "./assets/fonts/press_start_2p.ttf", fontSize = 24},
        {fontId = "press_start_32", filePath = "./assets/fonts/press_start_2p.ttf", fontSize = 32},
        {fontId = "press_start_50", filePath = "./assets/fonts/press_start_2p.ttf", fontSize = 50},

    },
        sounds = {
        [0] = {soundId = "main_song", filePath = "./assets/sounds/main_song.mp3"},
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
                {
            components = {
                sprite = {
                    assetId = "background02",
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
            components = { -- sonido
                sound = {
                    soundId = "main_song",
                    volume = 20,
                    loops = -1,
                    autoPlay = true,
                    active = true,
                },
            }

        },
        -- Player
       {
            components = {
                clickable = {

                },
                text = {
                    text = "Crimson",
                    fontId = "press_start_50",
                    r = 255,
                    g = 255,
                    b = 255,
                    a = 255,

                },
                transform = {
                    position = {
                        x = 221,
                        y = 90
                    },
                    scale = {
                        x = 1.2,
                        y = 1.2
                    },
                    rotation = 0.0
                },
            }
        },
        -- Player
        {
            components = {
                clickable = {

                },
                text = {
                    text = "Crimson",
                    fontId = "press_start_50",
                    r = 118,
                    g = 199,
                    b = 242,
                    a = 255,

                },
                transform = {
                    position = {
                        x = 225,
                        y = 90
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

                text = {
                    text = "Ganaste",
                    fontId = "press_start_24",
                    r = 150,
                    g = 255,
                    b = 0,
                    a = 255,

                },
                transform = {
                    position = {
                        x = 305,
                        y = 285
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
                clickable = {

                },
                script = {
                    
                    path = "./assets/scripts/end_button_01.lua"
                    
                },
                text = {
                    text = "Regresar al menu",
                    fontId = "press_start_24",
                    r = 150,
                    g = 255,
                    b = 0,
                    a = 255,

                },
                transform = {
                    position = {
                        x = 350,
                        y = 375
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
                clickable = {

                },
                script = {
                    
                    path = "./assets/scripts/menu_button_03.lua"
                    
                },
                text = {
                    text = "Reintentar",
                    fontId = "press_start_24",
                    r = 150,
                    g = 255,
                    b = 0,
                    a = 255,

                },
                transform = {
                    position = {
                        x = 270,
                        y = 465
                    },
                    scale = {
                        x = 1.0,
                        y = 1.0
                    },
                    rotation = 0.0
                },
            }
        },
    
    }
}