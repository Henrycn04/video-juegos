#ifndef CLICKEVENT_HPP
#define CLICKEVENT_HPP

#include "../ECS/ECS.hpp"
#include "../EventManager/Event.hpp"

/**
 * @brief Event representing a mouse click action
 * 
 * Contains information about the mouse button clicked
 * and the screen coordinates where the click occurred.
 * Inherits from the base Event class for use with EventManager.
 */
class ClickEvent : public Event {
public:
    int buttonCode;  ///< SDL button code of the mouse button clicked
    int x;          ///< X-coordinate of the click position
    int y;          ///< Y-coordinate of the click position

    /**
     * @brief Construct a new Click Event object
     * 
     * @param buttonCode SDL button code (default: 0)
     * @param x X-coordinate of click (default: 0)
     * @param y Y-coordinate of click (default: 0)
     */
    ClickEvent(int buttonCode = 0, int x = 0, int y = 0) {
        this->buttonCode = buttonCode;
        this->x = x;
        this->y = y;
    }
};

#endif // CLICKEVENT_HPP