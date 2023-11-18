#include "common.h"
#include "Character.h"

const float Character::JUKKYJUNG_SCALE = 1.0f; // Adjust the scale as needed
const sf::Vector2f Character::JUKKYJUNG_POSITION = { 0.0f, 0.0f }; // Adjust the position as needed

Character::Character(const std::string& name, int health, int baseAttack, ElementalPower elementalPower)
    : name(name), health(health), baseAttack(baseAttack), elementalPower(elementalPower) {
    FileManager::LoadFromFile(this->m_TextFont, "asset/font/ReadexPro.ttf");
    FileManager::LoadFromFile(this->m_JukkyJungTexture, "asset/picture/JukkyJung.png");

    this->m_JukkyJungHp.setFillColor(sf::Color::Black);
    this->m_JukkyJungHp.setFont(this->m_TextFont);
    this->m_JukkyJungHp.setString("HP: 100");

    this->m_JukkyJungSprite.setTexture(this->m_JukkyJungTexture);
    this->m_JukkyJungSprite.setScale({ this->JUKKYJUNG_SCALE, this->JUKKYJUNG_SCALE });
    this->m_JukkyJungSprite.setPosition(this->JUKKYJUNG_POSITION);
}

// Getter for elemental power
ElementalPower Character::getElementalPower() const {
    return elementalPower;
}

// Getter for character name
const std::string& Character::getName() const {
    return name;
}

// Getter for current health
int Character::getHealth() const {
    return health;
}

// Getter for base attack
int Character::getBaseAttack() const {
    return baseAttack;
}

// Check if the character is defeated
bool Character::isDefeated() const {
    return health <= 0;
}

// Function to reduce health by a specified amount
void Character::takeDamage(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
}

// Function to draw the character on the game window
void Character::draw(sf::RenderWindow* window) {
    window->draw(this->m_JukkyJungSprite);
}