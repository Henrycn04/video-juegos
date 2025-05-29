#ifndef CIRCLECOLLIDERCOMPONENT_HPP
#define CIRCLECOLLIDERCOMPONENT_HPP

/**
 * @struct CircleColliderComponent
 * @brief Component for defining a circular collider in the ECS.
 */
struct CircleColliderComponent {
    /** @brief Radius of the circular collider. */
    int radius;

    /** @brief Width of the collider's bounding box. */
    int width;

    /** @brief Height of the collider's bounding box. */
    int height;

    /**
     * @brief Constructs a CircleColliderComponent with specified parameters.
     * @param radius The radius of the circular collider (default: 0).
     * @param width The width of the collider's bounding box (default: 0).
     * @param height The height of the collider's bounding box (default: 0).
     */
    CircleColliderComponent(int radius = 0, int width = 0, int height = 0) {
        this->width = width;
        this->height = height;
        this->radius = radius;
    }
};

#endif