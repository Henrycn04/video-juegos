#ifndef CLICKEVENT_HPP
#define CLICKEVENT_HPP
#include "../ECS/ECS.hpp"
#include "../EventManager/Event.hpp"

class ClickEvent : public Event {
    public: 
        int buttonCode;
        int x;
        int y;
        ClickEvent(int buttonCode = 0, int x = 0, int y = 0) {
            this->buttonCode = buttonCode;
            this->x = x;
            this->y = y;
        }


};

#endif // CLICKEVENT_HPP