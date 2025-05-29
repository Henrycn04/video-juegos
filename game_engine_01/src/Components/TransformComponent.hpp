#ifndef TRANSFORM_COMPONENT_HPP
#define TRANSFORM_COMPONENT_HPP
#include <../libs/glm/glm.hpp>

/**
 * @brief Component that handles entity transformation properties
 * 
 * Stores position, scale, and rotation information for entity transformation.
 */
struct TransformComponent {
    glm::vec2 position;  ///< 2D position vector (x,y coordinates)
    glm::vec2 scale;     ///< 2D scale vector (width,height multipliers)
    double rotation;     ///< Rotation angle in degrees

    /**
     * @brief Construct a new Transform Component object
     * 
     * @param position Initial position (default: (0.0, 0.0))
     * @param scale Initial scale (default: (1.0, 1.0))
     * @param rotation Initial rotation in degrees (default: 0.0)
     */
    TransformComponent(glm::vec2 position = glm::vec2(0.0,0.0), 
                      glm::vec2 scale = glm::vec2(1.0,1.0), 
                      double rotation = 0.0) {
        this->position = position;
        this->scale = scale;
        this->rotation = rotation;
    }
};

#endif // TRANSFORM_COMPONENT_HPP