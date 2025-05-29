#ifndef PROJECTILECOMPONENT_HPP
#define PROJECTILECOMPONENT_HPP

#include <../libs/glm/glm.hpp>

/**
 * @struct ProjectileComponent
 * @brief Component for managing projectile properties in the ECS.
 */
struct ProjectileComponent {
    /** @brief Velocity vector of the projectile. */
    glm::vec2 velocity;

    /** @brief Position vector of the projectile. */
    glm::vec2 position;

    /** @brief Scale vector of the projectile. */
    glm::vec2 scale;

    /** @brief Rotation angle of the projectile in radians. */
    double rotation;

    /** @brief Indicates whether the projectile has hit a target. */
    bool hasHit = false;

    /** @brief Damage dealt by the projectile upon impact. */
    int damage;

    /**
     * @brief Constructs a ProjectileComponent with specified parameters.
     * @param position Initial position of the projectile (default: (0.0, 0.0)).
     * @param scale Scale of the projectile (default: (1.0, 1.0)).
     * @param rotation Initial rotation in radians (default: 0.0).
     * @param velocity Initial velocity vector (default: (0.0, 0.0)).
     */
    ProjectileComponent(glm::vec2 position = glm::vec2(0.0, 0.0), glm::vec2 scale = glm::vec2(1.0, 1.0), double rotation = 0.0, const glm::vec2& velocity = glm::vec2(0.0f, 0.0f)) {
        this->velocity = velocity;
        this->position = position;
        this->scale = scale;
        this->rotation = rotation;
    }
};

#endif