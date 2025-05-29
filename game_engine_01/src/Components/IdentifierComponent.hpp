#ifndef IDENTIFIERCOMPONENT_HPP
#define IDENTIFIERCOMPONENT_HPP

#include <string>

/**
 * @struct IdentifierComponent
 * @brief Component for assigning an identifier and name to an entity in the ECS.
 */
struct IdentifierComponent {
    /** @brief Unique identifier for the entity. */
    int id;

    /** @brief Name associated with the entity. */
    std::string name;

    /**
     * @brief Default constructor for IdentifierComponent.
     */
    IdentifierComponent() = default;

    /**
     * @brief Constructs an IdentifierComponent with specified ID and name.
     * @param id The unique identifier for the entity.
     * @param name The name associated with the entity.
     */
    IdentifierComponent(int id, const std::string& name)
        : id(id), name(name) {}
};

#endif