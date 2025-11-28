#pragma once
#include <string>
#include <vector>

class Character {
public:
    Character(const std::string& name, int health, int attack);

    const std::string& getName() const;
    int getHealth() const;
    int getAttack() const;

    void takeDamage(int damage);

private:
    std::string name;
    int health;
    int attack;
};
