#ifndef IDENTIFIERCOMPONENT_CPP
#define IDENTIFIERCOMPONENT_CPP

#include <string>
struct IdentifierComponent {
    int id;
    std::string name;

    IdentifierComponent() = default;

    IdentifierComponent(int id, const std::string& name)
        : id(id), name(name) {}
};


#endif