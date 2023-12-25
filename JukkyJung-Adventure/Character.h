#pragma once
#include "common.h"

// Enum to represent elemental powers
enum class ElementalPower {
    Fire, Water, Wind, Earth, Darkness, Light, Poison, Nature, Speed, Mind, Time, Ice, Gravity
};

// Class to represent a character in the game
class Character {
public:
    // Explicit constructor to initialize the Character object
    explicit Character();

    // Getter methods for individual attributes
    std::string getName(const std::string& characterName) const;
    int getHealth(const std::string& characterName) const;
    int getAttack(const std::string& characterName) const;
    ElementalPower getElementalPower(const std::string& characterName) const;

    // Setter methods for individual attributes
    void setName(const std::string& characterName, const std::string& newName);
    void setHealth(const std::string& characterName, int newHealth);
    void setAttack(const std::string& characterName, int newAttack);
    void setElementalPower(const std::string& characterName, ElementalPower newElementalPower);

    // Private helper function to add a character with specified attributes
    void addCharacter(const std::string& name, int health, int attack, ElementalPower elementalPower, const std::string& characterTexturePath);

    // Function to draw the character on the game window
    void draw(sf::RenderWindow* window, std::string name);

private:
    // Struct to represent attributes of the character
    struct CharacterAttributes {
        std::string name;
        int health;
        int attack;
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
    sf::Font textFont;

    // Unordered map to store attributes of different characters
    std::unordered_map<std::string, CharacterAttributes> charactersAttributes;

	// Private helper function to get attributes of a character by name
    const CharacterAttributes& setCharacterAttributes(const std::string& characterName) const;

    // Private helper function to get attributes of a character by name
    CharacterAttributes& getCharacterAttributes(const std::string& characterName);
};
