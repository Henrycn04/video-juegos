#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <map>
#include <memory>
#include <sol/sol.hpp>
#include <string>
#include "../SceneManager/SceneLoader.hpp"

/**
 * @brief Manages game scenes and scene transitions
 *
 * Handles loading, running, and switching between different game scenes.
 * Maintains a collection of available scenes and manages scene lifecycle.
 */
class SceneManager {
private:
    std::map<std::string, std::string> scenes;  ///< Map of scene names to their file paths
    std::string nextScene;                      ///< Name of the scene to load next
    bool isSceneRunning = false;                ///< Flag indicating if a scene is currently active
    std::unique_ptr<SceneLoader> sceneLoader;   ///< Loader for scene resources and entities

public:
    /**
     * @brief Construct a new Scene Manager object
     */
    SceneManager();

    /**
     * @brief Destroy the Scene Manager object
     */
    ~SceneManager();

    /**
     * @brief Load scene configuration from a Lua script
     * @param scenePath Path to the scene configuration file
     * @param lua Reference to the Lua state
     */
    void LoadSceneFromScript(const std::string& scenePath, sol::state& lua);

    /**
     * @brief Load the currently set next scene
     */
    void LoadScene();

    /**
     * @brief Get the name of the next scene to be loaded
     * @return std::string Name of the next scene
     */
    std::string GetNextScene() const;

    /**
     * @brief Set the next scene to be loaded
     * @param nextScene Name of the next scene
     */
    void SetNextScene(const std::string& nextScene);

    /**
     * @brief Check if a scene is currently running
     * @return true if a scene is active
     * @return false if no scene is active
     */
    bool IsSceneRunning() const;

    /**
     * @brief Mark the scene as started/running
     */
    void StartScene();

    /**
     * @brief Mark the scene as stopped
     */
    void StopScene();
};

#endif // SCENEMANAGER_HPP