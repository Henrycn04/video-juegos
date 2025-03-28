#include "ECS.hpp"

int IComponent::nextId = 0;

int Entity::GetId() const{
    return id;
}