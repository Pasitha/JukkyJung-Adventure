#pragma once
#include "common.h"

class Combat {
public:
    Combat(const std::vector<Character>& team1, const std::vector<Character>& team2);

    void PerformAttack(const std::vector<Character>& team1, const std::vector<Character>& team2);

private:
    std::vector<Character> team1;
    std::vector<Character> team2;
};
