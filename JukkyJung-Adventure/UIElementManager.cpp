#include "UIElementManager.h"

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

    // Set initial properties for the sprite
    elementSprite.setScale({ 1.75f, 2.75f });

    // Set initial properties for the text
    elementText.setFillColor(sf::Color(0, 0, 0));
    elementText.setFont(elementFont);
    elementText.setScale({ 1.5f, 1.5f });

    // Set the texture for the sprite
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
    // Set the text for the button
    elementText.setString(buttonLabel);

    // Set the position for the button sprite
    elementSprite.setPosition(buttonPosition);

    // Add button components (sprite and text) to the map
    elementComponents[numberOfElements] = std::make_pair(elementSprite, elementText);
    elementInfo[numberOfElements] = std::make_pair("button", alignment);

    // Update text position based on alignment
    updateTextPosition(numberOfElements);

    // Set the initial state for the button
    elementStates[numberOfElements] = ElementState::Normal;

    // Increment the number of elements
    numberOfElements++;
}

// Add a new buttons with a given label, position, and text alignment for many buttons
void UIElementManager::addButton(const std::vector<std::pair<std::string, sf::Vector2f>>& buttons, TextAlignment alignment) {
    for (const auto& button : buttons) {
		// Set the text for the button
		elementText.setString(button.first);

		// Set the position for the button sprite
		elementSprite.setPosition(button.second);

		// Add button components (sprite and text) to the map
		elementComponents[numberOfElements] = std::make_pair(elementSprite, elementText);
		elementInfo[numberOfElements] = std::make_pair("button", alignment);

		// Update text position based on alignment
		updateTextPosition(numberOfElements);

		// Set the initial state for the button
		elementStates[numberOfElements] = ElementState::Normal;

		// Increment the number of elements
		numberOfElements++;
    }
}


// Add a new slider with a given label, position, and size
void UIElementManager::addSlider(const std::string& sliderLabel, const sf::Vector2f& sliderPosition, const sf::Vector2f& sliderSize) {
    // Create a slider rectangle shape
    sf::RectangleShape slider;
    slider.setPosition(sliderPosition);
    slider.setSize(sliderSize);
    slider.setFillColor(NORMAL_COLOR);

    // Set the text for the slider
    elementText.setString(sliderLabel);

    // Update text position based on alignment
    updateTextPosition(numberOfElements);

    // Add slider components (sprite and text) to the map
    elementComponents[numberOfElements] = std::make_pair(elementSprite, elementText);
    sliders[numberOfElements] = slider;

    // Set the initial state for the slider
    elementInfo[numberOfElements] = std::make_pair("slider", TextAlignment::Center);
    elementStates[numberOfElements] = ElementState::Normal;

    // Increment the number of elements
    numberOfElements++;
}

// Set the position of an element by its ID
void UIElementManager::setPosition(unsigned short elementId, const sf::Vector2f& position) {
    // Get the type of element (button or slider)
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
    // Get the type of element (button or slider)
    auto& elementType = elementInfo[elementId].first;

    // Determine the color based on the state
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

    // Set the color for the element
    if (elementType == "button") {
        auto& elementComponent = elementComponents[elementId];
        elementComponent.first.setColor(color);
    }
    else if (elementType == "slider") {
        auto& slider = sliders[elementId];
        slider.setFillColor(color);
    }

    // Update the state of the element
    elementStates[elementId] = state;
}

// Check if any element is being hovered and update states
void UIElementManager::updateHover() {
    // Get the current mouse position
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*windowInstance);

    for (auto& [id, components] : elementComponents) {
        auto& elementType = elementInfo[id].first;

        if (elementType == "button") {
            auto& [sprite, text] = components;

            // Check if the mouse is over the button
            sf::FloatRect bounds = sprite.getGlobalBounds();
            if (bounds.contains(static_cast<sf::Vector2f>(mousePosition))) {
#ifdef _DEBUG
                std::cout << "Element ID: " << id << " text : " << text.getString().operator std::string() << " Update to hoverfrom line : " << __LINE__ << std::endl;
#endif
                setColor(id, ElementState::Hovered);
            } else {
#ifdef _DEBUG
                std::cout << "Element ID: " << id << " text : " << text.getString().operator std::string() << " Update to normal from line : " << __LINE__ << std::endl;
#endif
                setColor(id, ElementState::Normal);
            }
        } else if (elementType == "slider") {
            auto& slider = sliders[id];

            // Check if the mouse is over the slider
            sf::FloatRect bounds = slider.getGlobalBounds();
            if (bounds.contains(static_cast<sf::Vector2f>(mousePosition))) {
                setColor(id, ElementState::Hovered);
            } else {
                setColor(id, ElementState::Normal);
            }
        }
    }
}

// Get the ID of the element being hovered (-1 if none)
int UIElementManager::whichElementHover() const {
    // Get the current mouse position
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*windowInstance);

    for (const auto& [id, components] : elementComponents) {
        const auto& elementType = elementInfo.at(id).first;

        if (elementType == "button") {
            const auto& sprite = components.first;

            // Check if the mouse is over the button
            sf::FloatRect bounds = sprite.getGlobalBounds();
            if (bounds.contains(static_cast<sf::Vector2f>(mousePosition))) {
                return static_cast<int>(id);
            }
        } else if (elementType == "slider") {
            const auto& slider = sliders.at(id);

            // Check if the mouse is over the slider
            sf::FloatRect bounds = slider.getGlobalBounds();
            if (bounds.contains(static_cast<sf::Vector2f>(mousePosition))) {
                return static_cast<int>(id);
            }
        }
    }

    // Return -1 if no element is being hovered
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
        } else if (elementType == "slider") {
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
    } else if (elementType == "slider") {
        auto& slider = sliders[elementId];
        auto& text = elementComponents[elementId].second;

        text.setPosition(
            slider.getPosition().x + slider.getGlobalBounds().width / 2.f - text.getGlobalBounds().width / 2.f,
            slider.getPosition().y + slider.getGlobalBounds().height / 3.5f - text.getGlobalBounds().height / 3.5f);
    }
}

