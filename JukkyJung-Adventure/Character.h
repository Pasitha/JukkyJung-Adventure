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
    // Getter for current health
    int getHealth() const;
    // Getter for base attack
    int getBaseAttack() const;
    // Check if the character is defeated (health <= 0)
    bool isDefeated() const;
    // Function to reduce health by a specified amount
    void takeDamage(int damage);
    // Function to draw the character on the game window
    void draw(sf::RenderWindow* window);

private:
    std::string name;
    int health;
    int baseAttack;
    ElementalPower elementalPower;

    // Constants for positioning and scaling of the character sprite
    static const float JUKKYJUNG_SCALE;
    static const sf::Vector2f JUKKYJUNG_POSITION;

    // Texture and sprite for the character
    sf::Texture m_JukkyJungTexture;
    sf::Sprite m_JukkyJungSprite;

    // Font and text for displaying health
    sf::Font m_TextFont;
    sf::Text m_JukkyJungHp;
};

