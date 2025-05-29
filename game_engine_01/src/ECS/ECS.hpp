#ifndef ECS_HPP
#define ECS_HPP

#include <cstddef>
#include <bitset>
#include <memory>
#include <vector>
#include <set>
#include <deque>
#include <typeindex>
#include <unordered_map>
#include <iostream>
#include "../Utils/Pool.hpp"

/** @brief Maximum number of components allowed in the ECS. */
const unsigned int MAX_COMPONENTS = 64;

/** @brief Type alias for component signature using a bitset. */
typedef std::bitset<MAX_COMPONENTS> Signature;

/**
 * @class IComponent
 * @brief Base interface for components in the ECS.
 */
struct IComponent {
protected:
    /** @brief Static counter for assigning unique component IDs. */
    static int nextId;
};

/**
 * @class Component
 * @brief Templated base class for components, providing unique ID generation.
 * @tparam TComponent The specific component type.
 */
template <typename TComponent>
class Component : public IComponent {
public: 
    /**
     * @brief Gets the unique ID for the component type.
     * @return The component's unique ID.
     */
    static int GetId() {
        static int id = nextId++;
        return id;
    }
};

/**
 * @class Entity
 * @brief Represents an entity in the ECS, identified by a unique ID.
 */
class Entity {
private:
    /** @brief Unique identifier for the entity. */
    int id;

public:
    /**
     * @brief Constructs an entity with a given ID.
     * @param id The unique identifier for the entity.
     */
    Entity(int id) : id(id) {}

    /**
     * @brief Gets the entity's ID.
     * @return The entity's unique ID.
     */
    int GetId() const;

    /**
     * @brief Marks the entity for deletion.
     */
    void Kill();

    /**
     * @brief Equality operator for comparing entities.
     * @param other The other entity to compare with.
     * @return True if the entities have the same ID, false otherwise.
     */
    bool operator==(const Entity& other) const { return id == other.id; }

    /**
     * @brief Inequality operator for comparing entities.
     * @param other The other entity to compare with.
     * @return True if the entities have different IDs, false otherwise.
     */
    bool operator!=(const Entity& other) const { return id != other.id; }

    /**
     * @brief Greater-than operator for comparing entities.
     * @param other The other entity to compare with.
     * @return True if this entity's ID is greater than the other's, false otherwise.
     */
    bool operator>(const Entity& other) const { return id > other.id; }

    /**
     * @brief Less-than operator for comparing entities.
     * @param other The other entity to compare with.
     * @return True if this entity's ID is less than the other's, false otherwise.
     */
    bool operator<(const Entity& other) const { return id < other.id; }

    /**
     * @brief Adds a component to the entity.
     * @tparam TComponent The type of component to add.
     * @tparam TArgs Parameter pack for component constructor arguments.
     * @param args Arguments to forward to the component's constructor.
     */
    template <typename TComponent, typename... TArgs>
    void AddComponent(TArgs&&... args);

    /**
     * @brief Removes a component from the entity.
     * @tparam TComponent The type of component to remove.
     */
    template <typename TComponent>
    void RemoveComponent();

    /**
     * @brief Checks if the entity has a specific component.
     * @tparam TComponent The type of component to check.
     * @return True if the entity has the component, false otherwise.
     */
    template <typename TComponent>
    bool HasComponent() const;

    /**
     * @brief Gets a reference to a specific component of the entity.
     * @tparam TComponent The type of component to retrieve.
     * @return Reference to the component.
     */
    template <typename TComponent>
    TComponent& GetComponent() const;

    /** @brief Pointer to the ECS registry managing this entity. */
    class Registry* registry;
};

/**
 * @class System
 * @brief Represents a system in the ECS that operates on entities with specific components.
 */
class System {
private:
    /** @brief Bitset representing the required components for this system. */
    Signature componentSignature;

    /** @brief List of entities managed by this system. */
    std::vector<Entity> entities;

public:
    /**
     * @brief Default constructor for the system.
     */
    System() = default;

    /**
     * @brief Default destructor for the system.
     */
    ~System() = default;

    /**
     * @brief Adds an entity to the system.
     * @param entity The entity to add.
     */
    void AddEntityToSystem(Entity entity);

    /**
     * @brief Removes an entity from the system.
     * @param entity The entity to remove.
     */
    void RemoveEntityFromSystem(Entity entity);

    /**
     * @brief Gets the list of entities managed by this system.
     * @return A vector of entities.
     */
    std::vector<Entity> GetSystemEntities() const;

    /**
     * @brief Gets the component signature of the system.
     * @return The system's component signature.
     */
    const Signature& GetComponentSignature() const;

    /**
     * @brief Specifies a required component for the system.
     * @tparam TComponent The type of component required.
     */
    template <typename TComponent> 
    void RequireComponent();
};

/**
 * @class Registry
 * @brief Manages entities, components, and systems in the ECS.
 */
class Registry {
private:
    /** @brief Number of entities in the registry. */
    int numEntity = 0;

    /** @brief Vector of component pools, one for each component type. */
    std::vector<std::shared_ptr<IPool>> componentsPools;

    /** @brief Vector of signatures for each entity's components. */
    std::vector<Signature> entityComponentSignatures;

    /** @brief Map of systems, indexed by their type. */
    std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

    /** @brief Set of entities pending addition to the registry. */
    std::set<Entity> entitiesToBeAdded;

    /** @brief Set of entities pending deletion from the registry. */
    std::set<Entity> entitiesToBeKilled;

    /** @brief Deque of reusable entity IDs. */
    std::deque<int> freeIds;

public:
    /**
     * @brief Constructs a new registry.
     */
    Registry();

    /**
     * @brief Destroys the registry and its resources.
     */
    ~Registry();

    /**
     * @brief Updates the registry, processing pending entity additions and deletions.
     */
    void Update();

    /**
     * @brief Creates a new entity in the registry.
     * @return The created entity.
     */
    Entity CreateEntity();

    /**
     * @brief Marks an entity for deletion.
     * @param entity The entity to delete.
     */
    void KillEntity(Entity entity);

    /**
     * @brief Adds a component to an entity.
     * @tparam TComponent The type of component to add.
     * @tparam TArgs Parameter pack for component constructor arguments.
     * @param entity The entity to add the component to.
     * @param args Arguments to forward to the component's constructor.
     */
    template <typename TComponent, typename... TArgs>
    void AddComponent(Entity entity, TArgs&&... args);

    /**
     * @brief Removes a component from an entity.
     * @tparam TComponent The type of component to remove.
     * @param entity The entity to remove the component from.
     */
    template <typename TComponent>
    void RemoveComponent(Entity entity);

    /**
     * @brief Checks if an entity has a specific component.
     * @tparam TComponent The type of component to check.
     * @param entity The entity to check.
     * @return True if the entity has the component, false otherwise.
     */
    template <typename TComponent>
    bool HasComponent(Entity entity) const;

    /**
     * @brief Gets a reference to a specific component of an entity.
     * @tparam TComponent The type of component to retrieve.
     * @param entity The entity to retrieve the component from.
     * @return Reference to the component.
     */
    template <typename TComponent>
    TComponent& GetComponent(Entity entity) const;

    /**
     * @brief Adds a system to the registry.
     * @tparam TSystem The type of system to add.
     * @tparam TArgs Parameter pack for system constructor arguments.
     * @param args Arguments to forward to the system's constructor.
     */
    template <typename TSystem, typename... TArgs>
    void AddSystem(TArgs&&... args);

    /**
     * @brief Removes a system from the registry.
     * @tparam TSystem The type of system to remove.
     */
    template <typename TSystem>
    void RemoveSystem();

    /**
     * @brief Checks if a system exists in the registry.
     * @tparam TSystem The type of system to check.
     * @return True if the system exists, false otherwise.
     */
    template <typename TSystem>
    bool HasSystem() const;

    /**
     * @brief Gets a reference to a specific system.
     * @tparam TSystem The type of system to retrieve.
     * @return Reference to the system.
     */
    template <typename TSystem>
    TSystem& GetSystem() const;

    /**
     * @brief Adds an entity to the relevant systems based on its components.
     * @param entity The entity to add.
     */
    void AddEntityToSystems(Entity entity);

    /**
     * @brief Removes an entity from all systems.
     * @param entity The entity to remove.
     */
    void RemoveEntityFromSystems(Entity entity);

    /**
     * @brief Gets all entities associated with a specific system.
     * @tparam T The type of system to query.
     * @return A vector of entities in the system.
     */
    template<typename T>
    std::vector<Entity> GetEntitiesFromSystem();

    /**
     * @brief Clears all entities from the registry.
     */
    void ClearAllEntities();
};

/**
 * @brief Specifies a required component for a system.
 * @tparam TComponent The type of component required.
 */
template <typename TComponent>
void System::RequireComponent() {
    const int componentId = Component<TComponent>::GetId();
    componentSignature.set(componentId);
}

/**
 * @brief Gets all entities associated with a specific system.
 * @tparam T The type of system to query.
 * @return A vector of entities in the system.
 */
template<typename T>
std::vector<Entity> Registry::GetEntitiesFromSystem() {
    if (!HasSystem<T>()) return {};

    auto& systemDerived = GetSystem<T>();
    return systemDerived.GetSystemEntities();
}

/**
 * @brief Adds a component to an entity in the registry.
 * @tparam TComponent The type of component to add.
 * @tparam TArgs Parameter pack for component constructor arguments.
 * @param entity The entity to add the component to.
 * @param args Arguments to forward to the component's constructor.
 */
template <typename TComponent, typename... TArgs>
void Registry::AddComponent(Entity entity, TArgs&&... args) {
    const int componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();

    if (static_cast<long unsigned int>(componentId) >= componentsPools.size()) {
        componentsPools.resize(componentId + 10, nullptr);
    }

    if (!componentsPools[componentId]) {
        std::shared_ptr<Pool<TComponent>> newComponentPool = std::make_shared<Pool<TComponent>>();
        componentsPools[componentId] = newComponentPool;
    }

    std::shared_ptr<Pool<TComponent>> componentPool 
        = std::static_pointer_cast<Pool<TComponent>>(componentsPools[componentId]); 
    
    if (entityId >= componentPool->GetSize()) {
        componentPool->Resize(numEntity + 100);
    } 

    TComponent newComponent(std::forward<TArgs>(args)...);
    componentPool->Set(entityId, newComponent);
    entityComponentSignatures[entityId].set(componentId);
}

/**
 * @brief Removes a component from an entity in the registry.
 * @tparam TComponent The type of component to remove.
 * @param entity The entity to remove the component from.
 */
template <typename TComponent>
void Registry::RemoveComponent(Entity entity) {
    const int componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();

    entityComponentSignatures[entityId].set(componentId, false);
}

/**
 * @brief Checks if an entity has a specific component in the registry.
 * @tparam TComponent The type of component to check.
 * @param entity The entity to check.
 * @return True if the entity has the component, false otherwise.
 */
template <typename TComponent>
bool Registry::HasComponent(Entity entity) const {
    const int componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();

    return entityComponentSignatures[entityId].test(componentId);
}

/**
 * @brief Gets a reference to a specific component of an entity in the registry.
 * @tparam TComponent The type of component to retrieve.
 * @param entity The entity to retrieve the component from.
 * @return Reference to the component.
 */
template <typename TComponent>
TComponent& Registry::GetComponent(Entity entity) const {
    const int componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();

    auto componentPool = 
        std::static_pointer_cast<Pool<TComponent>>(componentsPools[componentId]);
    return componentPool->Get(entityId);
}

/**
 * @brief Adds a system to the registry.
 * @tparam TSystem The type of system to add.
 * @tparam TArgs Parameter pack for system constructor arguments.
 * @param args Arguments to forward to the system's constructor.
 */
template <typename TSystem, typename... TArgs>
void Registry::AddSystem(TArgs&&... args) {
    std::shared_ptr<TSystem> newSystem = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
    systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

/**
 * @brief Removes a system from the registry.
 * @tparam TSystem The type of system to remove.
 */
template <typename TSystem>
void Registry::RemoveSystem() {
    auto system = systems.find(std::type_index(typeid(TSystem)));
    systems.erase(system);
}

/**
 * @brief Checks if a system exists in the registry.
 * @tparam TSystem The type of system to check.
 * @return True if the system exists, false otherwise.
 */
template <typename TSystem>
bool Registry::HasSystem() const {
    return systems.find(std::type_index(typeid(TSystem))) != systems.end();
}

/**
 * @brief Gets a reference to a specific system in the registry.
 * @tparam TSystem The type of system to retrieve.
 * @return Reference to the system.
 */
template <typename TSystem>
TSystem& Registry::GetSystem() const {
    auto system = systems.find(std::type_index(typeid(TSystem)));
    return *(std::static_pointer_cast<TSystem>(system->second));
}

/**
 * @brief Adds a component to an entity through the entity interface.
 * @tparam TComponent The type of component to add.
 * @tparam TArgs Parameter pack for component constructor arguments.
 * @param args Arguments to forward to the component's constructor.
 */
template <typename TComponent, typename... TArgs>
void Entity::AddComponent(TArgs&&... args) {
    registry->AddComponent<TComponent>(*this, std::forward<TArgs>(args)...);
}

/**
 * @brief Removes a component from an entity through the entity interface.
 * @tparam TComponent The type of component to remove.
 */
template <typename TComponent>
void Entity::RemoveComponent() {
    registry->RemoveComponent<TComponent>(*this);
}

/**
 * @brief Checks if an entity has a specific component through the entity interface.
 * @tparam TComponent The type of component to check.
 * @return True if the entity has the component, false otherwise.
 */
template <typename TComponent>
bool Entity::HasComponent() const {
    return registry->HasComponent<TComponent>(*this);
}

/**
 * @brief Gets a reference to a specific component of an entity through the entity interface.
 * @tparam TComponent The type of component to retrieve.
 * @return Reference to the component.
 */
template <typename TComponent>
TComponent& Entity::GetComponent() const {
    return registry->GetComponent<TComponent>(*this);
}

#endif