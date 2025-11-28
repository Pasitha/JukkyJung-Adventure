#include "Enemy.h"

Enemy::Enemy(const std::string& name, int health, int attack)
    : name(name), health(health), attack(attack) {}

Enemy::~Enemy() {}

void Enemy::takeDamage(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
}

const std::string& Enemy::getName() const {
    return name;
}

int Enemy::getHealth() const {
    return health;
}

int Enemy::getAttack() const {
    return attack;
}
