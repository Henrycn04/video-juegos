#ifndef SCENELOADER_HPP
#define SCENELOADER_HPP

#include <SDL2/SDL.h>
#include <memory>
#include <sol/sol.hpp>
#include <string>
#include "../AssetManager/AssetManager.hpp"
#include "../ControllerManager/ControllerManager.hpp"
#include "../ECS/ECS.hpp"

/**
 * @brief Handles loading and parsing of game scenes from Lua configuration files
 * 
 * Manages loading of all scene components including assets, entities,
 * input mappings, and game objects.
 */
class SceneLoader {
private:
    /**
     * @brief Loads background assets from Lua configuration
     * @param renderer SDL renderer for texture creation
     * @param background Lua table containing background data
     * @param assetManager Asset manager for storing loaded assets
     */
    void LoadBackground(SDL_Renderer* renderer, const sol::table& background, std::unique_ptr<AssetManager>& assetManager);

    /**
     * @brief Loads sprite assets from Lua configuration
     * @param renderer SDL renderer for texture creation
     * @param sprites Lua table containing sprite data
     * @param assetManager Asset manager for storing loaded assets
     */
    void LoadSprites(SDL_Renderer* renderer, const sol::table& sprites, std::unique_ptr<AssetManager>& assetManager);

    /**
     * @brief Loads font assets from Lua configuration
     * @param fonts Lua table containing font data
     * @param assetManager Asset manager for storing loaded assets
     */
    void LoadFonts(const sol::table& fonts, std::unique_ptr<AssetManager>& assetManager);

    /**
     * @brief Loads sound assets from Lua configuration
     * @param sounds Lua table containing sound data
     * @param assetManager Asset manager for storing loaded assets
     */
    void LoadSounds(const sol::table& sounds, std::unique_ptr<AssetManager>& assetManager);

    /**
     * @brief Loads keyboard input mappings from Lua configuration
     * @param keys Lua table containing key mappings
     * @param controllerManager Controller manager for storing input mappings
     */
    void LoadKey(const sol::table& keys, std::unique_ptr<ControllerManager>& controllerManager);

    /**
     * @brief Loads button input mappings from Lua configuration
     * @param buttons Lua table containing button mappings
     * @param controllerManager Controller manager for storing input mappings
     */
    void LoadButtons(const sol::table& buttons, std::unique_ptr<ControllerManager>& controllerManager);
    
    /**
     * @brief Loads and creates entities from Lua configuration
     * @param lua Lua state reference
     * @param entities Lua table containing entity definitions
     * @param registry ECS registry for entity creation
     */
    void LoadEntities(sol::state& lua, const sol::table& entities, std::unique_ptr<Registry>& registry);

public:
    /**
     * @brief Construct a new Scene Loader object
     */
    SceneLoader();

    /**
     * @brief Destroy the Scene Loader object
     */
    ~SceneLoader();

    /**
     * @brief Loads a complete scene from Lua configuration file
     * @param scenePath Path to the scene configuration file
     * @param lua Lua state reference
     * @param assetManager Asset manager for storing loaded assets
     * @param controllerManager Controller manager for input mappings
     * @param registry ECS registry for entity management
     * @param renderer SDL renderer for texture creation
     */
    void LoadScene(const std::string& scenePath, sol::state& lua, 
        std::unique_ptr<AssetManager>& assetManager, std::unique_ptr<ControllerManager>& controllerManager, 
        std::unique_ptr<Registry>& registry, SDL_Renderer* renderer);
};

#endif // SCENELOADER_HPP