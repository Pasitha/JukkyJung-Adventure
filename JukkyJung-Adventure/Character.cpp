#include "common.h"
#include "Character.h"

const float Character::JUKKYJUNG_SCALE = 1.0f; // Adjust the scale as needed
const sf::Vector2f Character::JUKKYJUNG_POSITION = { 0.0f, 0.0f }; // Adjust the position as needed

Character::Character(const std::string& name, int health, int baseAttack, ElementalPower elementalPower)
    : m_windowInstance(nullptr), name(name), health(health), baseAttack(baseAttack), elementalPower(elementalPower) {
    FileManager::LoadFromFile(this->m_TextFont, "asset/font/ReadexPro.ttf");
    FileManager::LoadFromFile(this->m_JukkyJungTexture, "asset/picture/JukkyJung.png");

    m_JukkyJungHp.setFillColor(sf::Color::Black);
    m_JukkyJungHp.setFont(this->m_TextFont);
    m_JukkyJungHp.setString("HP: 100");

    this->m_JukkyJungSprite.setTexture(this->m_JukkyJungTexture);
    this->m_JukkyJungSprite.setScale({ this->JUKKYJUNG_SCALE, this->JUKKYJUNG_SCALE });
    this->m_JukkyJungSprite.setPosition(this->JUKKYJUNG_POSITION);
}

// Getter for elemental power
ElementalPower Character::getElementalPower() const {
    return elementalPower;
}

// Getter for base attack
int Character::getBaseAttack() const {
    return baseAttack;
}

// Getter for character name
const std::string& Character::getName() const {
    return name;
}