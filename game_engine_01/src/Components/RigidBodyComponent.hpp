#ifndef RIGIDBODYCOMPONENT_HPP
#define RIGIDBODYCOMPONENT_HPP

#include <glm/glm.hpp>

/**
 * @struct RigidBodyComponent
 * @brief Component for managing physics-related properties of an entity in the ECS.
 */
struct RigidBodyComponent {
    /** @brief Velocity vector of the entity. */
    glm::vec2 velocity;

    /**
     * @brief Constructs a RigidBodyComponent with a specified velocity.
     * @param velocity Initial velocity vector of the entity (default: (0.0, 0.0)).
     */
    RigidBodyComponent(const glm::vec2& velocity = glm::vec2(0.0f, 0.0f)) {
        this->velocity = velocity;
    }
};

#endif