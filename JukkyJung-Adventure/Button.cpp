// Button.cpp
#include "common.h"

// Constants for button colors
const sf::Color Button::NORMAL_COLOR = sf::Color(255, 255, 255, Button::COLOR_ALPHA_NORMAL);
const sf::Color Button::HOVER_COLOR = sf::Color(155, 155, 155, Button::COLOR_ALPHA_HOVER);

// Constructor to initialize the button
Button::Button(sf::RenderWindow* window) :
    windowInstance(window),
    numberOfButtons(0),
    buttonTexture(),
    buttonSprite(),
    buttonText(),
    buttonComponents()
{
    // Load font and texture from files
    FileManager::LoadFromFile(buttonFont, "asset/font/ReadexPro.ttf");
    FileManager::LoadFromFile(buttonTexture, "asset/picture/Button.png");

    // Set text properties
    buttonText.setFillColor(sf::Color(0, 0, 0));
    buttonText.setFont(buttonFont);
    
    // Set sprite texture
    buttonSprite.setTexture(buttonTexture);
}

// Destructor implementation only in debug mode
#ifdef _DEBUG
Button::~Button() {
    std::cout << "Button was destroyed!" << std::endl;
}
#endif

// Add a new button with a given label and position
void Button::addButton(const std::string& buttonLabel, const sf::Vector2f& buttonPosition) {
    // Set button text and position
    buttonText.setString(buttonLabel);
    buttonSprite.setPosition(buttonPosition);
    buttonText.setPosition({
        buttonSprite.getPosition().x + buttonSprite.getGlobalBounds().width / 2.f - buttonText.getGlobalBounds().width / 2.f,
        buttonSprite.getPosition().y + buttonSprite.getGlobalBounds().height / 2.2f - buttonText.getGlobalBounds().height / 2.2f
    });

    // Add button components to the map
    buttonComponents[numberOfButtons++] = std::make_pair(buttonSprite, buttonText);
}

// Set the position of a button by its ID
void Button::setPosition(unsigned short buttonId, const sf::Vector2f& position) {
    auto& buttonComponent = buttonComponents[buttonId];
    buttonComponent.first.setPosition(position);
    buttonComponent.second.setPosition({
        buttonComponent.first.getPosition().x + buttonComponent.first.getGlobalBounds().width / 2.f - buttonComponent.second.getGlobalBounds().width / 2.f,
        buttonComponent.first.getPosition().y + buttonComponent.first.getGlobalBounds().height / 2.2f - buttonComponent.second.getGlobalBounds().height / 2.2f
    });
}

// Set the color of a button by its ID
void Button::setDefaultColor(unsigned short buttonId) {
    auto& buttonComponent = buttonComponents[buttonId];
    buttonComponent.first.setColor(NORMAL_COLOR);
}

// Check if any button is being hovered and apply hover effect
void Button::isHover() {
    // Get mouse position
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*windowInstance);

    // Iterate through button components and apply hover effect
    for (auto& [id, components] : buttonComponents) {
        auto& [sprite, text] = components;

        sf::Vector2f btnPosition = sprite.getPosition();
        sf::FloatRect btnLocalBounds = sprite.getLocalBounds();

        float btnxPosWidth = btnPosition.x + btnLocalBounds.width;
        float btnyPosHeight = btnPosition.y + btnLocalBounds.height;

        // Check if the mouse is over the button
        if (mousePosition.x < btnxPosWidth && mousePosition.x > btnPosition.x && mousePosition.y < btnyPosHeight && mousePosition.y > btnPosition.y) {
            sprite.setColor(HOVER_COLOR);
        }
        else {
            sprite.setColor(NORMAL_COLOR);
        }
    }
}

// Get the ID of the button being hovered (-1 if none)
int Button::whichButtonHover() {
    // Get mouse position
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*windowInstance);

    // Iterate through button components and return the ID of the hovered button
    for (auto& [id, components] : buttonComponents) {
        auto& [sprite, text] = components;

        sf::Vector2f btnPosition = sprite.getPosition();
        sf::FloatRect btnLocalBounds = sprite.getLocalBounds();

        float btnxPosWidth = btnPosition.x + btnLocalBounds.width;
        float btnyPosHeight = btnPosition.y + btnLocalBounds.height;

        // Check if the mouse is over the button
        if (mousePosition.x < btnxPosWidth && mousePosition.x > btnPosition.x && mousePosition.y < btnyPosHeight && mousePosition.y > btnPosition.y) {
            return static_cast<int>(id);
        }
    }
    return -1;
}

// Update and render the buttons
void Button::update() {
    // Iterate through button components and render them
    for (auto& [id, components] : buttonComponents) {
        auto& [sprite, text] = components;
        windowInstance->draw(sprite);
        windowInstance->draw(text);
    }
}
