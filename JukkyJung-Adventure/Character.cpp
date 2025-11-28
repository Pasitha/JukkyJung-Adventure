#include "Character.h"

Character::Character(const std::string& name, int health, int attack)
    : name(name), health(health), attack(attack) {}

const std::string& Character::getName() const {
    return name;
}

int Character::getHealth() const {
    return health;
}

int Character::getAttack() const {
    return attack;
}

void Character::takeDamage(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
}
