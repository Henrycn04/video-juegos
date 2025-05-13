#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <string>
#include "../Game/Game.hpp"
#include "../ECS/ECS.hpp"
#include "../Components/RigidBodyComponent.hpp"
bool IsActionActivated(const std::string& action) {
    return Game::GetInstance().controllerManager->IsActionActivated(action);
}


//RigidBody component

void SetVelocity(Entity entity, float x, float y) {
    auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
    rigidBody.velocity.x = x;
    rigidBody.velocity.y = y;
}

void GoToScene(const std::string& sceneName) {
    Game::GetInstance().sceneManager->SetNextScene(sceneName);
    Game::GetInstance().sceneManager->StopScene();
}

#endif // LUABINDING_HPP