#pragma once
#include "common.h"

// Enum to represent elemental powers
enum class ElementalPower {
    Fire,
    Water,
    Wind,
    Earth,
    Darkness,
    Light,
    Poison,
    Nature,
    Speed,
    Mind,
    Time,
    Ice,
    Gravity
};

class Character {
private:
    std::string name;
    int health;
    ElementalPower elementalPower; // New member for elemental power

public:
    // Constructor with elemental power parameter
    Character(const std::string& name, int health, ElementalPower elementalPower);

    // Getter for elemental power
    ElementalPower getElementalPower() const;

};
