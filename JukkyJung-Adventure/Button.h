#pragma once
#include "UIElement.h"
#include <functional>

/**
 * @class Button
 * @brief A clickable button UI element.
 *
 * This class implements a standard button that can be clicked to trigger an action.
 * It inherits from the UIElement base class.
 */
class Button : public UIElement {
public:
    /**
     * @brief Constructs a Button object.
     * @param text The text to be displayed on the button.
     * @param font The font to be used for the button's text.
     * @param position The position of the button on the screen.
     * @param onClick A callback function to be executed when the button is clicked.
     */
    Button(const std::string& text, const sf::Font& font, const sf::Vector2f& position, std::function<void()> onClick);

    void handleEvent(sf::Event& event) override;
    void update(sf::Time deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    bool isMouseOver(sf::Vector2f mousePos) override;

private:
    sf::Text text;
    sf::RectangleShape shape;
    std::function<void()> onClick;
    bool isPressed;
};
