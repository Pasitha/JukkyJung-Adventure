#include "UIElementManager.h"
#include "common.h"

// Constants for element colors
const sf::Color UIElementManager::NORMAL_COLOR = sf::Color(255, 255, 255, UIElementManager::COLOR_ALPHA_NORMAL);
const sf::Color UIElementManager::HOVER_COLOR = sf::Color(155, 155, 155, UIElementManager::COLOR_ALPHA_HOVER);
const sf::Color UIElementManager::PRESSED_COLOR = sf::Color(100, 100, 100, UIElementManager::COLOR_ALPHA_PRESSED);

// Constructor to initialize the UI element manager
UIElementManager::UIElementManager(sf::RenderWindow* window)
    : windowInstance(window),
    numberOfElements(0),
    elementTexture(),
    elementSprite(),
    elementText(),
    elementComponents(),
    elementInfo(),
    elementStates(),
    sliders()
{
    // Load font and texture from files
    FileManager::LoadFromFile(elementFont, "asset/UI/Font/kenvector_future.ttf");
    FileManager::LoadFromFile(elementTexture, "asset/UI/PNG/grey_button15.png");

    elementSprite.setScale({ 1.75f, 2.75f });

    // Set text properties
    elementText.setFillColor(sf::Color(0, 0, 0));
    elementText.setFont(elementFont);
    elementText.setScale({ 1.5f, 1.5f });

    // Set sprite texture
    elementSprite.setTexture(elementTexture);
}

// Destructor implementation only in debug mode
#ifdef _DEBUG
UIElementManager::~UIElementManager() {
    std::cout << "UIElementManager was destroyed!" << std::endl;
}
#endif

// Add a new button with a given label, position, and text alignment
void UIElementManager::addButton(const std::string& buttonLabel, const sf::Vector2f& buttonPosition, TextAlignment alignment) {
    elementText.setString(buttonLabel);

    elementSprite.setPosition(buttonPosition);
    updateTextPosition(numberOfElements);  // Update text position based on alignment

    // Add button components to the map
    elementComponents[numberOfElements] = std::make_pair(elementSprite, elementText);
    elementInfo[numberOfElements] = std::make_pair("button", alignment);
    elementStates[numberOfElements] = ElementState::Normal;
    numberOfElements++;
}

// Add a new slider with a given label, position, and size
void UIElementManager::addSlider(const std::string& sliderLabel, const sf::Vector2f& sliderPosition, const sf::Vector2f& sliderSize) {
    sf::RectangleShape slider;
    slider.setPosition(sliderPosition);
    slider.setSize(sliderSize);
    slider.setFillColor(NORMAL_COLOR);

    elementText.setString(sliderLabel);
    updateTextPosition(numberOfElements);  // Update text position based on alignment

    // Add slider components to the map
    elementComponents[numberOfElements] = std::make_pair(elementSprite, elementText);
    sliders[numberOfElements] = slider;
    elementInfo[numberOfElements] = std::make_pair("slider", TextAlignment::Center);  // Default alignment for sliders
    elementStates[numberOfElements] = ElementState::Normal;
    numberOfElements++;
}

// Set the position of an element by its ID
void UIElementManager::setPosition(unsigned short elementId, const sf::Vector2f& position) {
    auto& elementType = elementInfo[elementId].first;

    if (elementType == "button") {
        auto& elementComponent = elementComponents[elementId];
        elementComponent.first.setPosition(position);
        updateTextPosition(elementId);
    }
    else if (elementType == "slider") {
        auto& slider = sliders[elementId];
        slider.setPosition(position);
        updateTextPosition(elementId);
    }
}

// Set the color of an element by its ID and state
void UIElementManager::setColor(unsigned short elementId, ElementState state) {
    auto& elementType = elementInfo[elementId].first;

    sf::Color color;
    switch (state) {
    case ElementState::Normal:
        color = NORMAL_COLOR;
        break;
    case ElementState::Hovered:
        color = HOVER_COLOR;
        break;
    case ElementState::Pressed:
        color = PRESSED_COLOR;
        break;
    }

    if (elementType == "button") {
        auto& elementComponent = elementComponents[elementId];
        elementComponent.first.setColor(color);
    }
    else if (elementType == "slider") {
        auto& slider = sliders[elementId];
        slider.setFillColor(color);
    }

    elementStates[elementId] = state;
}

// Check if any element is being hovered and update states
void UIElementManager::updateHover() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*windowInstance);

    for (auto& [id, components] : elementComponents) {
        auto& elementType = elementInfo[id].first;

        if (elementType == "button") {
            auto& [sprite, text] = components;

            sf::FloatRect bounds = sprite.getGlobalBounds();
            if (bounds.contains(static_cast<sf::Vector2f>(mousePosition))) {
                setColor(id, ElementState::Hovered);
            }
            else {
                setColor(id, ElementState::Normal);
            }
        }
        else if (elementType == "slider") {
            auto& slider = sliders[id];

            sf::FloatRect bounds = slider.getGlobalBounds();
            if (bounds.contains(static_cast<sf::Vector2f>(mousePosition))) {
                setColor(id, ElementState::Hovered);
            }
            else {
                setColor(id, ElementState::Normal);
            }
        }
    }
}

// Get the ID of the element being hovered (-1 if none)
int UIElementManager::whichElementHover() const {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*windowInstance);

    for (const auto& [id, components] : elementComponents) {
        const auto& elementType = elementInfo.at(id).first;

        if (elementType == "button") {
            const auto& sprite = components.first;

            sf::FloatRect bounds = sprite.getGlobalBounds();
            if (bounds.contains(static_cast<sf::Vector2f>(mousePosition))) {
                return static_cast<int>(id);
            }
        }
        else if (elementType == "slider") {
            const auto& slider = sliders.at(id);

            sf::FloatRect bounds = slider.getGlobalBounds();
            if (bounds.contains(static_cast<sf::Vector2f>(mousePosition))) {
                return static_cast<int>(id);
            }
        }
    }

    return -1;
}

// Update and render the elements
void UIElementManager::update() {
    for (const auto& [id, components] : elementComponents) {
        const auto& elementType = elementInfo.at(id).first;

        if (elementType == "button") {
            const auto& [sprite, text] = components;
            windowInstance->draw(sprite);
            windowInstance->draw(text);
        }
        else if (elementType == "slider") {
            const auto& slider = sliders.at(id);
            windowInstance->draw(slider);
            const auto& text = components.second;
            windowInstance->draw(text);
        }
    }
}

// Update text position based on element type and alignment
void UIElementManager::updateTextPosition(unsigned short elementId) {
    auto& elementType = elementInfo[elementId].first;
    auto alignment = elementInfo[elementId].second;

    if (elementType == "button") {
        auto& elementComponent = elementComponents[elementId];
        auto& sprite = elementComponent.first;
        auto& text = elementComponent.second;

        switch (alignment) {
        case TextAlignment::Left:
            text.setPosition(sprite.getPosition().x, sprite.getPosition().y);
            break;
        case TextAlignment::Center:
            text.setPosition(
                sprite.getPosition().x + sprite.getGlobalBounds().width / 2.f - text.getGlobalBounds().width / 2.f,
                sprite.getPosition().y + sprite.getGlobalBounds().height / 3.5f - text.getGlobalBounds().height / 3.5f);
            break;
        case TextAlignment::Right:
            text.setPosition(
                sprite.getPosition().x + sprite.getGlobalBounds().width - text.getGlobalBounds().width,
                sprite.getPosition().y);
            break;
        }
    }
    else if (elementType == "slider") {
        auto& slider = sliders[elementId];
        auto& text = elementComponents[elementId].second;

        text.setPosition(
            slider.getPosition().x + slider.getGlobalBounds().width / 2.f - text.getGlobalBounds().width / 2.f,
            slider.getPosition().y + slider.getGlobalBounds().height / 3.5f - text.getGlobalBounds().height / 3.5f);
    }
}
