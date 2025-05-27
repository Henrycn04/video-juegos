#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <glm/glm.hpp>
#include <iostream>
#include <sol/sol.hpp>  // Sol2 al final
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include "../AssetManager/AssetManager.hpp"
#include "../ControllerManager/ControllerManager.hpp"
#include "../EventManager/EventManager.hpp"
#include "../ECS/ECS.hpp"
#include "../SceneManager/SceneManager.hpp"
const int FPS = 30;
const int MILLISECS_PER_FRAME = 1000 / FPS;


class Game {
private:

    SDL_Window* window = nullptr;


    int millisecsPreviousFrame = 0;
    bool isRunning = false;

    int mPreviousFrame = 0;
public:
    SDL_Renderer* renderer = nullptr;
    size_t windowWidth = 0;
    size_t windowHeight = 0;
    std::unique_ptr<ControllerManager> controllerManager;
    std::unique_ptr<AssetManager> assetManager;
    std::unique_ptr<EventManager> eventManager;
    std::unique_ptr<Registry> registry;
    std::unique_ptr<SceneManager> sceneManager;
    sol::state lua;
    int enemiesLeftToSpawn = 0;
    int enemiesLeft = 0;
    int totalPoints = 0;
    int totalPointsPrev = 0;
    bool finDelNivel = false;
    bool win = false;
    bool isPaused = false;

private:
    void Setup();
    void RunScene();
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