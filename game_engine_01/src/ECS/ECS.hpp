#ifndef ECS_HPP
#define ECS_HPP


#include <memory>
#include <vector>
#include "../Utils/Pool.hpp"


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

};

class Registry {
    private:
        int numEntity = 0;
        std::vector<std::shared_ptr<IPool>> componentsPools;
};

#endif