#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include "Event.hpp"
#include <list>
#include <memory>
#include <functional>
#include <iostream>
#include <map>
#include <typeindex>

/**
 * @brief Interface for event callback functionality
 * 
 * Base class for implementing event callbacks with type erasure.
 */
class IEventCallback {
public:
    virtual ~IEventCallback() = default;

    /**
     * @brief Executes the callback with the given event
     * @param event The event to process
     */
    void Excute(Event& event) {
        Call(event);
    }

private:
    /**
     * @brief Internal callback implementation
     * @param event The event to process
     */
    virtual void Call(Event& event) = 0;
};

/**
 * @brief Templated event callback implementation
 * @tparam TOwner Type of the owner class
 * @tparam TEvent Type of the event to handle
 */
template<typename TOwner, typename TEvent>
class EventCallback : public IEventCallback {
private:
    typedef void (TOwner::*CallbackFunction)(TEvent&);
    TOwner* ownerInstance;        ///< Pointer to the owner instance
    CallbackFunction callbackFunction; ///< Pointer to member function

    /**
     * @brief Internal callback implementation
     * @param event The event to process (will be cast to TEvent)
     */
    virtual void Call(Event& event) override {
        std::invoke(callbackFunction, ownerInstance, static_cast<TEvent&>(event));
    }

public:
    /**
     * @brief Construct a new Event Callback object
     * @param owner Pointer to the owner instance
     * @param callback Pointer to member function to call
     */
    EventCallback(TOwner* owner, CallbackFunction callback) {
        this->ownerInstance = owner;
        this->callbackFunction = callback;
    }
};

typedef std::list<std::unique_ptr<IEventCallback>> HandlerList; ///< List of event handlers

/**
 * @brief Manages event subscriptions and dispatching
 * 
 * Implements a publish-subscribe pattern with type-safe event handling.
 */
class EventManager {
private:
    std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers; ///< Map of event types to their handlers

public:
    /**
     * @brief Construct a new Event Manager object
     */
    EventManager() {
        std::cout << "[EventManager] Se ejecuta constructor" << std::endl;
    };

    /**
     * @brief Destroy the Event Manager object
     */
    ~EventManager() {
        std::cout << "[EventManager] Se ejecuta destructor" << std::endl;
    };

    /**
     * @brief Clears all event subscriptions
     */
    void Restart() {
        subscribers.clear();
    };

    /**
     * @brief Subscribe to an event type
     * @tparam TOwner Type of the owner class
     * @tparam TEvent Type of the event to subscribe to
     * @param owner Pointer to the owner instance
     * @param callback Member function to call when event occurs
     */
    template<typename TOwner, typename TEvent>
    void SubscribeToEvent(TOwner* owner, void (TOwner::*callback)(TEvent&)) {
        if (!subscribers[typeid(TEvent)].get()) {
            subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
        }
        auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(owner, callback);
        subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
    };

    /**
     * @brief Emit an event to all subscribers
     * @tparam TEvent Type of the event to emit
     * @tparam TArgs Argument types for event construction
     * @param args Arguments to forward to event constructor
     */
    template<typename TEvent, typename... TArgs>
    void EmitEvent(TArgs&&... args) {
        auto handlers = subscribers[typeid(TEvent)].get();
        if (handlers) {
            for (auto it = handlers->begin(); it != handlers->end(); ++it) {
                auto handler = it->get();
                TEvent event(std::forward<TArgs>(args)...);
                handler->Excute(event);
            }
        }
    };
};

#endif // EVENTMANAGER_HPP