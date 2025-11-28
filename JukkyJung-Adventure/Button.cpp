#include "Button.h"

Button::Button(const std::string& text, const sf::Font& font, const sf::Vector2f& position, std::function<void()> onClick)
    : onClick(onClick), isPressed(false) {
    this->text.setString(text);
    this->text.setFont(font);
    this->text.setPosition(position);
    this->text.setCharacterSize(30);

    shape.setPosition(position);
    shape.setSize({ 200, 50 });
    shape.setFillColor(sf::Color::White);
}

void Button::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (isMouseOver({ (float)event.mouseButton.x, (float)event.mouseButton.y })) {
            isPressed = true;
        }
    }
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        if (isPressed) {
            isPressed = false;
            if (isMouseOver({ (float)event.mouseButton.x, (float)event.mouseButton.y })) {
                onClick();
            }
        }
    }
}

void Button::update(sf::Time deltaTime) {
    if (isPressed) {
        shape.setFillColor(sf::Color(200, 200, 200));
    }
    else {
        shape.setFillColor(sf::Color::White);
    }
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

bool Button::isMouseOver(sf::Vector2f mousePos) {
    return shape.getGlobalBounds().contains(mousePos);
}
