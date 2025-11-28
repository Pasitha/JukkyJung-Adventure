#include "CheckBox.h"

CheckBox::CheckBox(const sf::Font& font, const sf::Vector2f& position, const std::string& label, std::function<void(bool)> onStateChanged)
    : checked(false), onStateChanged(onStateChanged) {
    this->label.setString(label);
    this->label.setFont(font);
    this->label.setPosition(position);
    this->label.setCharacterSize(20);

    box.setPosition({ position.x + 150, position.y });
    box.setSize({ 20, 20 });
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(1);

    check.setPosition({ position.x + 155, position.y + 5 });
    check.setSize({ 10, 10 });
    check.setFillColor(sf::Color::Black);
}

void CheckBox::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (isMouseOver({ (float)event.mouseButton.x, (float)event.mouseButton.y })) {
            setChecked(!checked);
        }
    }
}

void CheckBox::update(sf::Time deltaTime) {
    // Nothing to update for the checkbox
}

void CheckBox::draw(sf::RenderWindow& window) {
    window.draw(label);
    window.draw(box);
    if (checked) {
        window.draw(check);
    }
}

bool CheckBox::isMouseOver(sf::Vector2f mousePos) {
    return box.getGlobalBounds().contains(mousePos);
}

bool CheckBox::isChecked() const {
    return checked;
}

void CheckBox::setChecked(bool checked) {
    this->checked = checked;
    onStateChanged(checked);
}
