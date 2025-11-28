#pragma once
#include "UIElement.h"
#include <functional>

/**
 * @class Slider
 * @brief A slider UI element for selecting a value within a range.
 *
 * This class implements a slider with a draggable thumb, allowing the user to select
 * a value. It inherits from the UIElement base class.
 */
class Slider : public UIElement {
public:
    /**
     * @brief Constructs a Slider object.
     * @param font The font to be used for the slider's label.
     * @param position The position of the slider on the screen.
     * @param label The text label to be displayed next to the slider.
     * @param min The minimum value of the slider.
     * @param max The maximum value of the slider.
     * @param onValueChanged A callback function to be executed when the slider's value changes.
     */
    Slider(const sf::Font& font, const sf::Vector2f& position, const std::string& label, float min, float max, std::function<void(float)> onValueChanged);

    void handleEvent(sf::Event& event) override;
    void update(sf::Time deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    bool isMouseOver(sf::Vector2f mousePos) override;

    /**
     * @brief Gets the current value of the slider.
     * @return The current value.
     */
    float getValue() const;

private:
    sf::Text label;
    sf::RectangleShape track;
    sf::RectangleShape thumb;
    float minValue;
    float maxValue;
    float currentValue;
    bool isHeld;
    std::function<void(float)> onValueChanged;
};
