#pragma once
#include "common.h"

class Combat {
public:
    Combat(const std::vector<Character>& team1, const std::vector<Character>& team2)
        : team1(team1), team2(team2) {}

    void StartCombat();

private:
    std::vector<Character> team1;
    std::vector<Character> team2;

    bool IsCombatOngoing() const;
    void PerformRound();
    Character& ChooseTarget(std::vector<Character>& targetTeam);
};
