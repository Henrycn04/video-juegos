#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <../libs/glm/glm.hpp>
#include <iostream>
#include <../libs/sol/sol.hpp>  // Sol2 al final
#include <string>
#include <fstream>
#include <vector>
#include "Entities.h"


const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

struct windowData { // ya se usa
    int w, h, r, g, b;
};

struct fontData { // ya se usa
    std::string p;
    int r, g, b, s;
};




class Game {
private:
// Ventana
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    size_t windowWidth = 0;
    size_t windowHeight = 0;

    bool isRunning = false;
    bool isPaused = false;
    int mPreviousFrame = 0;

// Fuentes
    TTF_Font* font = nullptr;
    int fontSize = 0;
    SDL_Color fontColor = {0, 0, 0};



    void processInput();
    void update();
    void render();
    void readConfig();

    windowData windowD;
    fontData fontD;
    std::vector<entityData> entidades;
    
    std::vector<Entities> generados;
public:
    Game();
    ~Game();
    void init();
    void run();
    void destroy();
};
#endif