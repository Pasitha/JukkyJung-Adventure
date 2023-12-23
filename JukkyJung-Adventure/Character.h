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

// Class to represent a character in the game
class Character {
public:
    // Default constructor
    Character();

    // Getter for elemental power
    ElementalPower getElementalPower(std::string name) const;

    // Getter methods for individual attributes
    std::string getName(std::string characterName) const;
    int getHealth(std::string characterName) const;
    int getAttack(std::string characterName) const;
    ElementalPower getElementalPower(std::string characterName) const;

	// Setter methods for individual attributes
	void Character::setName(std::string characterName, const std::string& newName) {
		getCharacterAttributes(characterName).name = newName;
	}
	void Character::setHealth(std::string characterName, int newHealth) {
		getCharacterAttributes(characterName).health = newHealth;
	}
	void Character::setAttack(std::string characterName, int newAttack) {
		getCharacterAttributes(characterName).attack = newAttack;
	}
	void Character::setElementalPower(std::string characterName, ElementalPower newElementalPower) {
		getCharacterAttributes(characterName).elementalPower = newElementalPower;
	}

    // Function to draw the character on the game window
    // Parameters:
    // - window: Pointer to the game window
    // - name: Name of the character to be drawn
    void draw(sf::RenderWindow* window, std::string name);

private:
    // Struct to represent attributes of the character
    struct CharacterAttributes {
        // Name of the character
        std::string name;
        // Health points of the character
        int health;
        // Base attack points of the character
        int attack;
        // Elemental power of the character
        ElementalPower elementalPower;

        // Texture and sprite for character's visual representation
        sf::Texture texture;
        sf::Sprite sprite;

        // Font and text for displaying health
        sf::Text healthText;
    };

    // Static constant for scaling factor of the character
    static const float Scale;

    // Static font for text rendering
    static sf::Font textFont;

    // Unordered map to store attributes of different characters
    std::unordered_map<std::string, CharacterAttributes> charactersAttributes;

    // Private helper function to get attributes
    const CharacterAttributes& getCharacterAttributes(std::string name) const;

    // Private helper function to add a character
    void addCharacter(const std::string& name, int health, int attack, ElementalPower elementalPower, const std::string& characterTexturePath);
};
