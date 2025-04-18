#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP
#include "Event.hpp"
#include <list>
#include <memory>
#include <functional>
#include <iostream>
#include <map>
#include <typeindex>
class IEventCallback {
public:
    private: 
        virtual void Call(Event& event) = 0;
    public:
        virtual ~IEventCallback() = default;

        void Excute(Event& event) {
            Call(event);
        }
};


template<typename TOwner, typename TEvent>
class EventCallback : public IEventCallback {
    private:
        typedef void (TOwner::*CallbackFunction)(TEvent&);
        TOwner* ownerInstance;
        CallbackFunction callbackFunction;
        virtual void Call(Event& event) override {
            std::invoke(callbackFunction, ownerInstance, static_cast<TEvent&>(event));
        }
    public:
        EventCallback(TOwner* owner, CallbackFunction callback) {
            this->ownerInstance = owner;
            this->callbackFunction = callback;
        }
};

typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

class EventManager {
    private:
        std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;

    public:
        EventManager() {
            std::cout << "[EventManager] Se ejecuta constructor" << std::endl;
        };
        ~EventManager() {
            std::cout << "[EventManager] Se ejecuta destructor" << std::endl;
        };
        void Restart() {
            subscribers.clear();
        };
        template<typename TOwner, typename TEvent>
        void SubscribeToEvent(TOwner* owner, void (TOwner::*callback)(TEvent&)) {
            if (!subscribers[typeid(TEvent)].get()) {
                subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
            }
            auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(owner, callback);
            subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
        };

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
#endif