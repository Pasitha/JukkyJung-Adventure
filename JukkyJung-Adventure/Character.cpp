#include "common.h"

Character::Character(const std::string& name, int health, ElementalPower elementalPower)
    : name(name), health(health), elementalPower(elementalPower) {}

ElementalPower Character::getElementalPower() const {
    return elementalPower;
}
