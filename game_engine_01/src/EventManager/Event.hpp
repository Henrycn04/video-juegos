#ifndef EVENT_HPP
#define EVENT_HPP

/**
 * @brief Base class for event objects
 * 
 * Provides the foundation for event handling with default constructor
 * and virtual destructor for proper polymorphic behavior.
 * Can be extended to implement specific event types.
 */
class Event {
public:
    /**
     * @brief Construct a new Event object (default)
     */
    Event() = default;

    /**
     * @brief Destroy the Event object (virtual for proper inheritance)
     */
    virtual ~Event() = default;

    /**
     * @brief Execute the event's action
     */
    //virtual void execute() = 0;

    /**
     * @brief Undo the event's action
     */
    //virtual void undo() = 0;

    /**
     * @brief Redo the event's action
     */
    //virtual void redo() = 0;
    
};

#endif // EVENT_HPP