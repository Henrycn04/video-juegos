#include "ECS.hpp"
#include <algorithm>
int IComponent::nextId = 0;

int Entity::GetId() const{
    return id;
}
void System::AddEntityToSystem(Entity entity) {
    this->entities.push_back(entity);
}
void System::RemoveEntityFromSystem(Entity entity) {
    auto it = std::remove_if(entities.begin(), entities.end(), 
    [&entity](Entity other) {return entity == other;});
    entities.erase(it, entities.end());
}
std::vector<Entity> System::GetSystemEntities() const{
    return entities;
}
const Signature& System::GetComponentSignature() const {
    return componentSignature;
}

Registry::Registry() {
    std::cout<< "[Registry] Se ejecuta constructor" << std::endl;
}

Registry::~Registry() {
    std::cout<< "[Registry] Se ejecuta destructor" << std::endl;
}


// Entity management

Entity Registry::CreateEntity(){
    // TODO: reutilizar ids de entidades destruidas
    int entityId;
    if (freeIds.empty()) {
        entityId = numEntity++;
        if (static_cast<long unsigned int>(entityId) >= entityComponentSignatures.size()) {
            entityComponentSignatures.resize(entityId + 100);
        }
    } else {
        entityId = freeIds.front();
        freeIds.pop_front();
    }


    Entity entity(entityId);
    entity.registry = this;
    entitiesToBeAdded.insert(entity);

    std::cout << "[Registry] Se crea entidad " << entityId << std::endl;

    return entity;
}
void Registry::KillEntity(Entity entity){
    entitiesToBeKilled.insert(entity);
}

// add and remove entities to systems
void Registry::AddEntityToSystems(Entity entity){
    const int entityId = entity.GetId();

    const auto& entityComponentSignature = entityComponentSignatures[entityId];
    
    for (auto& system : systems) {
        const auto& systemComponentsSignature = system.second->GetComponentSignature();

        bool isInterested = (entityComponentSignature & systemComponentsSignature) == systemComponentsSignature;

        if (isInterested) {
            system.second->AddEntityToSystem(entity);
        }
    }
}
void Registry::RemoveEntityFromSystems(Entity entity){
    for (auto system : systems) {
        system.second->RemoveEntityFromSystem(entity);
    }
}
void Registry::Update(){
    for(auto entity : entitiesToBeAdded) {
        AddEntityToSystems(entity);
    }
    entitiesToBeAdded.clear();
    for(auto entity : entitiesToBeKilled) {
        RemoveEntityFromSystems(entity);
        entityComponentSignatures[entity.GetId()].reset();
        freeIds.push_back(entity.GetId());
    }
    entitiesToBeKilled.clear();
}