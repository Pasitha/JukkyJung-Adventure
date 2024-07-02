#include "common.h"

// Static constant for scaling factor of the character
const float Character::Scale = 0.3f;

// Constructor for the Character class
Character::Character(sf::RenderWindow* window) : windowInstance(window) {
    // Load font from file
    FileManager::LoadFromFile(textFont, "asset/font/ReadexPro.ttf");
}

// Getter method for character's name
std::string Character::getName(const std::string& characterName) const {
    return setCharacterAttributes(characterName).name;
}

// Getter method for character's health
int Character::getHealth(const std::string& characterName) const {
    return setCharacterAttributes(characterName).health;
}

// Getter method for character's attack points
int Character::getAttack(const std::string& characterName) const {
    return setCharacterAttributes(characterName).attack;
}

// Getter method for character's elemental power
ElementalPower Character::getElementalPower(const std::string& characterName) const {
    return setCharacterAttributes(characterName).elementalPower;
}

// Setter method to update character's name
void Character::setName(const std::string& characterName, const std::string& newName) {
    charactersAttributes[characterName].name = newName;
}

// Setter method to update character's health
void Character::setHealth(const std::string& characterName, int newHealth) {
    getCharacterAttributes(characterName).health = newHealth;
}

// Setter method to update character's attack points
void Character::setAttack(const std::string& characterName, int newAttack) {
    getCharacterAttributes(characterName).attack = newAttack;
}

// Setter method to update character's elemental power
void Character::setElementalPower(const std::string& characterName, ElementalPower newElementalPower) {
    getCharacterAttributes(characterName).elementalPower = newElementalPower;
}

// Private helper function to add a character with specified attributes
void Character::addCharacter(const std::string& name, int health, int attack, ElementalPower elementalPower, const std::string& characterTexturePath) {
    if (charactersAttributes.find(name) == charactersAttributes.end()) {
		auto& attributes = charactersAttributes[name];
		attributes.name = name;
		attributes.health = health;
		attributes.attack = attack;
		attributes.elementalPower = elementalPower;

		// Load texture from file
		FileManager::LoadFromFile(attributes.texture, characterTexturePath);

		// Set sprite properties
		attributes.sprite.setTexture(attributes.texture);
		attributes.sprite.setScale({ Scale, Scale });
    }
#ifdef _DEBUG
    else {
        std::cout << "Character already exists: " << name << std::endl;
    }
#endif
}

/*
void Character::setCharacterPosition(const std::string characterName, const sf::Vector2f& characterPosition, const bool isFlip = false) {
    charactersAttributes[characterName].sprite.setPosition(characterPosition);

    if (isFlip) {
		charactersAttributes[characterName].sprite.setScale(-1.f, 0.f);
    }
}
*/
// Function to draw the character on the game window
void Character::draw(std::string name) {
    windowInstance->draw(charactersAttributes[name].sprite);
}

// Setter method for character's attributes
const Character::CharacterAttributes& Character::setCharacterAttributes(const std::string& characterName) const {
    // Use find to check if the character with the given name exists
    auto it = charactersAttributes.find(characterName);

    // If found, return the attributes, otherwise throw an exception or handle the case appropriately
    if (it != charactersAttributes.end()) {
        return it->second;
    } else {
        // You may want to throw an exception or handle the case differently
        throw std::out_of_range("Character with name " + characterName  + " not found.");
    }
}

// Getter method for character's attributes
Character::CharacterAttributes& Character::getCharacterAttributes(const std::string& characterName) {
    // Use find to check if the character with the given name exists
    auto it = charactersAttributes.find(characterName);

    // If found, return the attributes, otherwise throw an exception or handle the case appropriately
    if (it != charactersAttributes.end()) {
        return it->second;
    } else {
        // You may want to throw an exception or handle the case differently
        throw std::out_of_range("Character with name " + characterName  + " not found.");
    }
}
