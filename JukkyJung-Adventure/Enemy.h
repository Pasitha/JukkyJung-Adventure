#pragma once
#include <string>

class Enemy {
public:
    Enemy(const std::string& name, int health, int attack);
    ~Enemy();

    void takeDamage(int damage);
    const std::string& getName() const;
    int getHealth() const;
    int getAttack() const;

private:
    std::string name;
    int health;
    int attack;
};
