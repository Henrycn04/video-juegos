#ifndef CLICKABLECOMPONENT_HPP
#define CLICKABLECOMPONENT_HPP

/**
 * @struct ClickableComponent
 * @brief Component for handling click interactions in the ECS.
 */
struct ClickableComponent {
    /** @brief Indicates whether the entity has been clicked. */
    bool isClicked;

    /**
     * @brief Constructs a ClickableComponent with default values.
     */
    ClickableComponent() {
        isClicked = false;
    }
};

#endif // CLICKABLECOMPONENT_HPP