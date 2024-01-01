#include "Combat.h"

Combat::Combat(const std::vector<Character>& team1, const std::vector<Character>& team2) : team1(team1), team2(team2) {

}

// Function to simulate a simple attack
void Combat::PerformAttack(Character& attacker, Character& target) {
#ifdef _DEBUG
	std::cout << "Start Combat!" << std::endl;
#endif
}
