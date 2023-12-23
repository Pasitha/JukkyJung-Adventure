#pragma once
#include "common.h"

// Forward declarations for classes used in Button
class Button;

// Button class is responsible for managing buttons, handling hover effects, and rendering them.
class Button {
public:
    // Constructor and destructor
    Button(sf::RenderWindow* window);
#ifdef _DEBUG
    ~Button();
#endif

    // Add a new button with a given label and position
    void addButton(const std::string& buttonLabel, const sf::Vector2f& buttonPosition);
    
    // Set the position of a button by its ID
    void setPosition(unsigned short buttonId, const sf::Vector2f& position);
    
    // Check if any button is being hovered and apply hover effect
    void isHover();
    
    // Get the ID of the button being hovered (-1 if none)
    int whichButtonHover();
    
    // Update and render the buttons
    void update();

private:
    // Constants for button colors
    static const sf::Color NORMAL_COLOR;
    static const sf::Color HOVER_COLOR;
    
    // Alpha values for color transparency
    static const int COLOR_ALPHA_NORMAL = 255;
    static const int COLOR_ALPHA_HOVER = 155;

    // Number of buttons
    size_t numberOfButtons;

    // Pointer to the SFML render window
    sf::RenderWindow* windowInstance;

    // SFML font, texture, sprite, and text for buttons
    sf::Font buttonFont;
    sf::Texture buttonTexture;
    sf::Sprite buttonSprite;
    sf::Text buttonText;

    // Map to associate button IDs with their components (Sprite and Text)
    std::map<unsigned short, std::pair<sf::Sprite, sf::Text>> buttonComponents;
};
