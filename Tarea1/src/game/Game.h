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

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

struct windowData {
    int w, h, r, g, b;
};

struct fontData {
    std::string p;
    int r, g, b, s;
};

struct entityData {
    std::string l, p;
    int w, h;
    glm::vec2 pos;
    glm::vec2 vel;
    double a;
};

class Game {
private:
// Ventana
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    size_t windowWidth = 0;
    size_t windowHeight = 0;

    bool isRunning = false;
    int mPreviousFrame = 0;

// Imagen
    SDL_Texture* imgTexture = nullptr;
    glm::vec2 pos = glm::vec2();
    glm::vec2 imgVel = glm::vec2();
    size_t imgWidth = 0;
    size_t imgHeight = 0;
    SDL_Rect srcRect = {0,0,0,0}; // pos, tamanno
    double angle = 0.0;

// Texto
    TTF_Font* font = nullptr;
    SDL_Texture* txtTexture = nullptr;
    int fontSize = 0;
    SDL_Color fontColor = {0, 0, 0};
    std::string message = "";
    glm::vec2 txtPos = glm::vec2();
    size_t txtWidth = 0;
    size_t txtHeight = 0;
    double txtAngle = 0.0;

    void processInput();
    void update();
    void render();
    void readConfig();
public:
    Game();
    ~Game();
    void init();
    void run();
    void destroy();
};
#endif