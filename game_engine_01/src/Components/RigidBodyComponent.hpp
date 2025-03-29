#ifndef RIGIDBODYCOMPONENT_HPP
#define RIGIDBODYCOMPONENT_HPP
#include <glm/glm.hpp>
struct RigidBodyComponent {
    glm::vec2 velocity;
    // glm::vec2 acceleration; de ser mas avanzado
    // bool isStatic; de ser mas avanzado
    RigidBodyComponent(const glm::vec2& velocity = glm::vec2(0.0f, 0.0f))
        {
            this->velocity = velocity;
        }
};


#endif