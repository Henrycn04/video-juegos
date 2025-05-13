#include "SceneManager.hpp"

#include <iostream>

#include "../Game/Game.hpp"

SceneManager::SceneManager() {
    std::cout << "[SceneManager] Constructor ejecutado" << std::endl;
    this->sceneLoader = std::make_unique<SceneLoader>();
}
SceneManager::~SceneManager() {
    sceneLoader.reset();
    std::cout << "[SceneManager] Destructor ejecutado" << std::endl;
}

void SceneManager::LoadSceneFromScript(const std::string& scenePath, sol::state& lua) {
    //TODO: Verificar codigo correcto con load result
    lua.script_file(scenePath);

    sol::table scenes = lua["scenes"];
    int index = 0;
    while (true) {
        sol::optional<sol::table> hasScene = scenes[index];
        if (hasScene == sol::nullopt) {
            break;
        }
        sol::table scene = scenes[index];
        this->scenes.emplace(scene["name"], scene["path"]);

        if (index == 0) {
            this->nextScene = scene["name"];
        }

        index++;
    }
}
void SceneManager::LoadScene(){
    Game& game = Game::GetInstance();
    std::string scenePath = scenes[nextScene];
    sceneLoader->LoadScene(scenePath, game.lua, game.assetManager, game.controllerManager, game.registry, game.renderer);
}

std::string SceneManager::GetNextScene() const {
    return nextScene;
}
void SceneManager::SetNextScene(const std::string& nextScene) {
    this->nextScene = nextScene;
    std::cout << "[SceneManager] Se establece la siguiente escena: " << nextScene << std::endl;
}

bool SceneManager::IsSceneRunning() const{
    return isSceneRunning;
}
void SceneManager::StartScene(){
    isSceneRunning = true;

}
void SceneManager::StopScene(){
    isSceneRunning = false;
}