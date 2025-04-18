#ifndef COLLISIONEVENT_HPP
#define COLLISIONEVENT_HPP
#include "../ECS/ECS.hpp"
#include "../EventManager/Event.hpp"
class CollisionEvent : public Event {
    public:
        Entity entityA;
        Entity entityB;
        CollisionEvent(Entity entityA, Entity entityB) : entityA(entityA), entityB(entityB) {
        };
        ~CollisionEvent() {
        };
};


#endif