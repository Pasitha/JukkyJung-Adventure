#include "Combat.h"

Combat::Combat(const std::vector<Character>& team1, const std::vector<Character>& team2) : team1(team1), team2(team2) {

}

// Function to simulate a simple attack
void Combat::PerformAttack(const std::vector<Character>& team1, const std::vector<Character>& team2) {
#ifdef _DEBUG
	std::cout << "Start Combat!" << std::endl;
#endif
    // Calculate damage, adjust HP, etc. (as previously discussed)

    // Trigger attack animation for the attacker
    // attacker.performAttackAnimation();

    // Trigger hit/damage animation for the target
    // target.receiveDamageAnimation();

    // Other animation-related logic as needed
}
