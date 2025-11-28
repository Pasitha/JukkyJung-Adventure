#include "Combat.h"
#include "Enemy.h"

Combat::Combat(std::unique_ptr<Character> player, std::unique_ptr<Enemy> enemy)
    : player(std::move(player)), enemy(std::move(enemy)), isPlayerTurn(true) {}

void Combat::start() {
    // Combat starts with the player's turn
    isPlayerTurn = true;
}

void Combat::playerAttack() {
    if (isPlayerTurn) {
        // Player attacks the enemy
        enemy->takeDamage(player->getAttack());
        if (enemy->getHealth() <= 0) {
            // Enemy is defeated
        } else {
            nextTurn();
        }
    }
}

void Combat::playerUseItem(const std::string& itemName) {
    if (isPlayerTurn) {
        // Player uses an item
        // player->useItem(itemName, *enemy);
        nextTurn();
    }
}

void Combat::nextTurn() {
    isPlayerTurn = !isPlayerTurn;
    if (!isPlayerTurn) {
        enemyTurn();
    }
}

void Combat::enemyTurn() {
    // Enemy attacks the player
    player->takeDamage(enemy->getAttack());
    if (player->getHealth() <= 0) {
        // Player is defeated
    } else {
        nextTurn();
    }
}
