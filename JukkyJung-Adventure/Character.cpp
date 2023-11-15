#include "common.h"

#include "Character.h"

// Constructor implementation
Character::Character(const std::string& name, int health, int baseAttack, ElementalPower elementalPower)
    : name(name), health(health), baseAttack(baseAttack), elementalPower(elementalPower) {}

// Getter for elemental power
ElementalPower Character::getElementalPower() const {
    return elementalPower;
}

// Getter for base attack
int Character::getBaseAttack() const {
    return baseAttack;
}
