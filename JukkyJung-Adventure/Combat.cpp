#include "Combat.h"

// Function to simulate a simple attack
void PerformAttack(Character& attacker, Character& target) {
    int damage = attacker.getBaseAttack();
#ifdef _DEBUG
    std::cout << attacker.getName() << " deals " << damage << " damage to " << target.getName() << std::endl;
#endif
    target.takeDamage(damage);
}

void Combat::StartCombat() {
    while (IsCombatOngoing()) {
        PerformRound();
    }
}

bool Combat::IsCombatOngoing() const {
    return !team1.empty() && !team2.empty();
}

void Combat::PerformRound() {
#ifdef _DEBUG
    std::cout << "Performing a round of combat!" << std::endl;
#endif
    Character& target = ChooseTarget((team1.size() > 0) ? team1 : team2);
    for (auto& attacker : team1) {
        PerformAttack(attacker, target);
    }

    for (auto& attacker : team2) {
        PerformAttack(attacker, target);
    }

    team1.erase(std::remove_if(team1.begin(), team1.end(), [](const Character& c) { return c.isDefeated(); }), team1.end());
    team2.erase(std::remove_if(team2.begin(), team2.end(), [](const Character& c) { return c.isDefeated(); }), team2.end());
}

Character& Combat::ChooseTarget(std::vector<Character>& targetTeam) {
    return targetTeam.front();
}
