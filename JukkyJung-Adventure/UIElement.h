#pragma once
#include <SFML/Graphics.hpp>

/**
 * @class UIElement
 * @brief An abstract base class for all UI elements in the game.
 *
 * This class defines the common interface that all UI elements, such as buttons and sliders,
 * must implement. It provides a consistent way to handle events, update state, and draw
 * the elements to the screen.
 */
class UIElement {
public:
    virtual ~UIElement() = default;

    /**
     * @brief Handles SFML events for the UI element.
     * @param event The SFML event to be processed.
     */
    virtual void handleEvent(sf::Event& event) = 0;

    /**
     * @brief Updates the UI element's logic.
     * @param deltaTime The time elapsed since the last frame.
     */
    virtual void update(sf::Time deltaTime) = 0;

    /**
     * @brief Draws the UI element to the render window.
     * @param window The sf::RenderWindow to draw to.
     */
    virtual void draw(sf::RenderWindow& window) = 0;

    /**
     * @brief Checks if the mouse is currently over the UI element.
     * @param mousePos The current position of the mouse.
     * @return True if the mouse is over the element, false otherwise.
     */
    virtual bool isMouseOver(sf::Vector2f mousePos) = 0;
};
