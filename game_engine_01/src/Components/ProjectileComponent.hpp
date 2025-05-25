#ifndef PROJECTILECOMPONENT
#define PROJECTILECOMPONENT
#include <../libs/glm/glm.hpp>

struct ProjectileComponent
{
    glm::vec2 velocity;
    glm::vec2 position;
    glm::vec2 scale;
    double rotation;
    bool hasHit = false;
    int damage;

    ProjectileComponent(glm::vec2 position = glm::vec2(0.0,0.0), glm::vec2 scale = glm::vec2(1.0,1.0), double rotation = 0.0, const glm::vec2& velocity = glm::vec2(0.0f, 0.0f)) {
        this->velocity = velocity;
        this->position = position;
        this->scale = scale;
        this->rotation = rotation;
    }
};










#endif