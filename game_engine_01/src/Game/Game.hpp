#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <glm/glm.hpp>
#include <iostream>
#include <sol/sol.hpp>  // Sol2 al final
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include "../ECS/ECS.hpp"

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;


class Game {
private:

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    size_t windowWidth = 0;
    size_t windowHeight = 0;

    bool isRunning = false;

    std::unique_ptr<Registry> registry;

    bool isPaused = false;
    int mPreviousFrame = 0;

private:
    void Setup();
    void processInput();
    void update();
    void render();
    void readConfig();
    Game();
    ~Game();

public:
    static Game& GetInstance();
    void init();
    void run();
    void destroy();
};
#endif