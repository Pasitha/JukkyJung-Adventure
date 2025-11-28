#pragma once
#include "Character.h"
#include <vector>
#include <memory>

class Enemy; // Forward declaration

class Combat {
public:
    Combat(std::unique_ptr<Character> player, std::unique_ptr<Enemy> enemy);

    void start();
    void playerAttack();
    void playerUseItem(const std::string& itemName);

private:
    void nextTurn();
    void enemyTurn();

    std::unique_ptr<Character> player;
    std::unique_ptr<Enemy> enemy;
    bool isPlayerTurn;
};
