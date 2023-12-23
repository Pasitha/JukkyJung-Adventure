#include "common.h"

const float Character::Scale = .3f;

Character::Character() {
	FileManager::LoadFromFile(this->textFont, "asset/font/ReadexPro.ttf");
}

// Implementation of getName method
std::string Character::getName(std::string characterName) const {
    return getCharacterAttributes(characterName).name;
}

// Implementation of getHealth method
int Character::getHealth(std::string characterName) const {
    return getCharacterAttributes(characterName).health;
}

// Implementation of getAttack method
int Character::getAttack(std::string characterName) const {
    return getCharacterAttributes(characterName).attack;
}

// Implementation of getElementalPower method
ElementalPower Character::getElementalPower(std::string characterName) const {
    return getCharacterAttributes(characterName).elementalPower;
}

// Setter methods for individual attributes
void Character::setName(std::string characterName, const std::string& newName) {
    charactersAttributes[characterName].name = newName;
}

void Character::setHealth(std::string characterName, int newHealth) {
    charactersAttributes[characterName].health = newHealth;
}

void Character::setAttack(std::string characterName, int newAttack) {
    charactersAttributes[characterName].attack = newAttack;
}

void Character::setElementalPower(std::string characterName, ElementalPower newElementalPower) {
    charactersAttributes[characterName].elementalPower = newElementalPower;
}

// Function to draw the character on the game window
void Character::draw(sf::RenderWindow* window, std::string name) {
    window->draw(this->charactersAttributes[name].sprite);
}

// Implementation of getCharacterAttributes method
const Character::CharacterAttributes& Character::getCharacterAttributes(std::string name) const {
    // Use find to check if the character with the given name exists
    auto it = charactersAttributes.find(name);

    // If found, return the attributes, otherwise throw an exception or handle the case appropriately
    if (it != charactersAttributes.end()) {
        return it->second;
    }
    else {
        // You may want to throw an exception or handle the case differently
        throw std::out_of_range("Character with name " + name + " not found.");
    }
}

void Character::addCharacter(const std::string& name, int health, int attack, ElementalPower elementalPower, const std::string& characterTexturePath) {
	this->charactersAttributes[name].name = name;
    this->charactersAttributes[name].health = 120;
    this->charactersAttributes[name].attack = 20;
    this->charactersAttributes[name].elementalPower = ElementalPower::Time;

    FileManager::LoadFromFile(this->charactersAttributes[name].texture, characterTexturePath);
}
