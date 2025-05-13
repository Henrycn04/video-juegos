#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <string>
#include "../Game/Game.hpp"
#include "../ECS/ECS.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/DrawableComponent.hpp"
#include <chrono>
bool IsActionActivated(const std::string& action) {
    return Game::GetInstance().controllerManager->IsActionActivated(action);
}

// Mouse
bool IsMouseButtonDown(const std::string& button_name) {
    return Game::GetInstance().controllerManager->IsMouseButtonDown(button_name);
}

std::tuple<int, int> GetMousePosition() {
    return Game::GetInstance().controllerManager->GetMousePosition();
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

void PushDrawPoint(Entity entity, int index, int x, int y) {
    auto& draw = entity.GetComponent<DrawableComponent>();
    if (index >= 0 && index < (int)draw.colorPoints.size()) {
        // Añadimos el punto con el timestamp
        draw.colorPoints[index].emplace_back(glm::vec2(x, y), std::chrono::steady_clock::now());
    }
}

#endif // LUABINDING_HPP