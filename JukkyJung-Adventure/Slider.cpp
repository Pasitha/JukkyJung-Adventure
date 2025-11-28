#include "Slider.h"

Slider::Slider(const sf::Font& font, const sf::Vector2f& position, const std::string& label, float min, float max, std::function<void(float)> onValueChanged)
    : minValue(min), maxValue(max), currentValue(min), isHeld(false), onValueChanged(onValueChanged) {
    this->label.setString(label);
    this->label.setFont(font);
    this->label.setPosition(position);
    this->label.setCharacterSize(20);

    track.setPosition({ position.x + 200, position.y + 5 });
    track.setSize({ 200, 10 });
    track.setFillColor(sf::Color(100, 100, 100));

    thumb.setPosition({ position.x + 200, position.y });
    thumb.setSize({ 20, 20 });
    thumb.setFillColor(sf::Color::White);
}

void Slider::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (isMouseOver({ (float)event.mouseButton.x, (float)event.mouseButton.y })) {
            isHeld = true;
        }
    }
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        isHeld = false;
    }
    if (event.type == sf::Event::MouseMoved && isHeld) {
        float newX = std::max(track.getPosition().x, std::min((float)event.mouseMove.x, track.getPosition().x + track.getSize().x));
        thumb.setPosition({ newX, thumb.getPosition().y });
        currentValue = minValue + ((thumb.getPosition().x - track.getPosition().x) / track.getSize().x) * (maxValue - minValue);
        onValueChanged(currentValue);
    }
}

void Slider::update(sf::Time deltaTime) {
    // Nothing to update for the slider
}

void Slider::draw(sf::RenderWindow& window) {
    window.draw(label);
    window.draw(track);
    window.draw(thumb);
}

bool Slider::isMouseOver(sf::Vector2f mousePos) {
    return thumb.getGlobalBounds().contains(mousePos);
}

float Slider::getValue() const {
    return currentValue;
}
