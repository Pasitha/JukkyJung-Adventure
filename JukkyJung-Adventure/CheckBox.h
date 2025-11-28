#pragma once
#include "UIElement.h"
#include <functional>

class CheckBox : public UIElement {
public:
    CheckBox(const sf::Font& font, const sf::Vector2f& position, const std::string& label, std::function<void(bool)> onStateChanged);

    void handleEvent(sf::Event& event) override;
    void update(sf::Time deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    bool isMouseOver(sf::Vector2f mousePos) override;

    bool isChecked() const;
    void setChecked(bool checked);

private:
    sf::Text label;
    sf::RectangleShape box;
    sf::RectangleShape check;
    bool checked;
    std::function<void(bool)> onStateChanged;
};
