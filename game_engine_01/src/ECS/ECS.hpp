#ifndef ECS_HPP
#define ECS_HPP

#include <bitset>
#include <memory>
#include <vector>
#include "../Utils/Pool.hpp"

const unsigned int MAX_COMPONENTS = 64;
typedef std::bitset<MAX_COMPONENTS> Signature;


struct IComponent {
    protected:
        static int nextId;
};

template <typename TComponent>
class Component : public IComponent {
    public: 
    static int GetId() {
        static int id = nextId++;
        return id;
    }
};

class Entity {
    private:
        int id;
    public:
        Entity(int id) : id(id){}
        int GetId() const;
};

class System {
    private:
        Signature componentSignature;
        std::vector<Entity> entities;

    public:
        System() = default;
        ~System() = default;
        void AddEntityToSystem(Entity entity);
        void RemoveEntityFromSystem(Entity entity);
        std::vector<Entity> GetSystemEntities() const;
        const Signature& GetComponentSignature() const;

        template <typename TComponent> 
        void RequireComponent();

};

class Registry {
    private:
        int numEntity = 0;
        std::vector<std::shared_ptr<IPool>> componentsPools;
};

template <typename TComponent>
void System::RequireComponent() {
    const int componentId = Component<TComponent>::GetId();
    componentSignature.set(componentId);
}

#endif