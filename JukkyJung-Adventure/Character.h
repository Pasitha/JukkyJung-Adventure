#pragma once
#include "common.h"

// Enum to represent elemental powers
enum class ElementalPower {
    Fire,
    Water,
    Wind,
    Earth,
    Darkness,
    Light,
    Poison,
    Nature,
    Speed,
    Mind,
    Time,
    Ice,
    Gravity
};

class Character {
public:
    // Constructor with elemental power and base attack parameters
    Character(const std::string& name, int health, int baseAttack, ElementalPower elementalPower);

    // Getter for elemental power
    ElementalPower getElementalPower() const;

    // Getter for character name
    const std::string& getName() const;

    // Getter for base attack
    int getBaseAttack() const;
private:
	sf::RenderWindow* m_windowInstance;
    std::string name;
    int health;
	sf::Font m_TextFont;
	sf::Text m_JukkyJungHp;
    int baseAttack;
    ElementalPower elementalPower;

	static const float JUKKYJUNG_SCALE;
	static const sf::Vector2f JUKKYJUNG_POSITION;

	sf::Texture m_JukkyJungTexture;
	sf::Sprite m_JukkyJungSprite;

};
