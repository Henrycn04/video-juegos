
scene = {
    -- Tabla de imagenes
    sprites = {
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
            components = {
                clickable = {

                },
                text = {
                    text = "Crimson Engine",
                    fontId = "press_start_32",
                    r = 150,
                    g = 0,
                    b = 150,
                    a = 255,

                },
                transform = {
                    position = {
                        x = 50,
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
        {
            components = {
                clickable = {

                },
                script = {
                    
                    path = "./assets/scripts/menu_button_01.lua"
                    
                },
                text = {
                    text = "Level 01",
                    fontId = "press_start_24",
                    r = 150,
                    g = 150,
                    b = 0,
                    a = 255,

                },
                transform = {
                    position = {
                        x = 50,
                        y = 150
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