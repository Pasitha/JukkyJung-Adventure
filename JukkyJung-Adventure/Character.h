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
    int baseAttack;
    ElementalPower elementalPower;

public:
    // Constructor with elemental power and base attack parameters
    Character(const std::string& name, int health, int baseAttack, ElementalPower elementalPower);

    // Getter for elemental power
    ElementalPower getElementalPower() const;

    // Getter for base attack
    int getBaseAttack() const;
};
