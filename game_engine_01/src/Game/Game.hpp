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

/** @brief Frames per second for the game. */
const int FPS = 30;

/** @brief Milliseconds per frame, calculated as 1000 / FPS. */
const int MILLISECS_PER_FRAME = 1000 / FPS;

/**
 * @class Game
 * @brief Main game class that manages the game loop, rendering, and resources.
 */
class Game {
private:
    /** @brief Pointer to the SDL window. */
    SDL_Window* window = nullptr;

    /** @brief Tracks the milliseconds of the previous frame for timing. */
    int millisecsPreviousFrame = 0;

    /** @brief Indicates whether the game is currently running. */
    bool isRunning = false;

    /** @brief Stores the index of the previous frame. */
    int mPreviousFrame = 0;

public:
    /** @brief SDL renderer for drawing graphics. */
    SDL_Renderer* renderer = nullptr;

    /** @brief Width of the game window. */
    size_t windowWidth = 0;

    /** @brief Height of the game window. */
    size_t windowHeight = 0;

    /** @brief Unique pointer to the controller manager for handling input. */
    std::unique_ptr<ControllerManager> controllerManager;

    /** @brief Unique pointer to the asset manager for handling game assets. */
    std::unique_ptr<AssetManager> assetManager;

    /** @brief Unique pointer to the event manager for handling game events. */
    std::unique_ptr<EventManager> eventManager;

    /** @brief Unique pointer to the ECS registry for managing entities and components. */
    std::unique_ptr<Registry> registry;

    /** @brief Unique pointer to the scene manager for handling game scenes. */
    std::unique_ptr<SceneManager> sceneManager;

    /** @brief Lua state for scripting support. */
    sol::state lua;

    /** @brief Number of enemies left to spawn in the current level. */
    int enemiesLeftToSpawn = 0;

    /** @brief Number of enemies currently active in the game. */
    int enemiesLeft = 0;

    /** @brief Total points accumulated by the player. */
    int totalPoints = 0;

    /** @brief Previous total points for tracking changes. */
    int totalPointsPrev = 0;

    /** @brief Indicates whether the current level has ended. */
    bool finDelNivel = false;

    /** @brief Indicates whether the player has won the game. */
    bool win = false;

    /** @brief Indicates whether the game is paused. */
    bool isPaused = false;

    /** @brief Index used for drawing order. */
    int drawIndex = -1;

    /** @brief Current level of the game. */
    int currentLevel = 0;

private:
    /**
     * @brief Initializes game resources and setup.
     */
    void Setup();

    /**
     * @brief Runs the current game scene.
     */
    void RunScene();

    /**
     * @brief Processes user input.
     */
    void processInput();

    /**
     * @brief Updates game state.
     */
    void update();

    /**
     * @brief Renders the game to the screen.
     */
    void render();

    /**
     * @brief Reads game configuration settings.
     */
    void readConfig();

    /**
     * @brief Constructor for the Game class (private for singleton pattern).
     */
    Game();

    /**
     * @brief Destructor for the Game class.
     */
    ~Game();

public:
    /**
     * @brief Gets the singleton instance of the Game class.
     * @return Reference to the Game instance.
     */
    static Game& GetInstance();

    /**
     * @brief Initializes the game, setting up SDL and other resources.
     */
    void init();

    /**
     * @brief Runs the main game loop.
     */
    void run();

    /**
     * @brief Cleans up and destroys game resources.
     */
    void destroy();
};

#endif