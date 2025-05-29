#ifndef COLLISIONEVENT_HPP
#define COLLISIONEVENT_HPP

#include "../ECS/ECS.hpp"
#include "../EventManager/Event.hpp"

/**
 * @brief Event representing a collision between two entities
 *
 * Contains references to both entities involved in the collision.
 * Inherits from the base Event class for use with the EventManager system.
 */
class CollisionEvent : public Event {
public:
    Entity entityA;  ///< First entity involved in the collision
    Entity entityB;  ///< Second entity involved in the collision

    /**
     * @brief Construct a new Collision Event object
     * @param entityA First entity in the collision
     * @param entityB Second entity in the collision
     */
    CollisionEvent(Entity entityA, Entity entityB) 
        : entityA(entityA), entityB(entityB) {
    };

    /**
     * @brief Destroy the Collision Event object
     */
    ~CollisionEvent() {
    };
};

#endif // COLLISIONEVENT_HPP