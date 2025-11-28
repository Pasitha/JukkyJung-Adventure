#pragma once
#include "common.h"

class Character; // Forward declaration

class Item {
public:
    Item(const std::string& name, const std::string& description);
    virtual ~Item() = default;

    virtual void use(Character& character) = 0;

    const std::string& getName() const { return name; }
    const std::string& getDescription() const { return description; }

protected:
    std::string name;
    std::string description;
};
