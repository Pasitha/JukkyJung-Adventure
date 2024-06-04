#include "UIElementManager.h"

// Constants for element colors
const sf::Color UIElementManager::NORMAL_COLOR = sf::Color(255, 255, 255, UIElementManager::COLOR_ALPHA_NORMAL);
const sf::Color UIElementManager::HOVER_COLOR = sf::Color(155, 155, 155, UIElementManager::COLOR_ALPHA_HOVER);
const sf::Color UIElementManager::PRESSED_COLOR = sf::Color(100, 100, 100, UIElementManager::COLOR_ALPHA_PRESSED);

// Constructor to initialize the UI element manager
UIElementManager::UIElementManager(sf::RenderWindow* window)
    : windowInstance(window),
      numberOfElements(0),
      sliders()
{
    // Load font and texture from files
    FileManager::LoadFromFile(elementFont, "asset/UI/Font/kenvector_future.ttf");
    FileManager::LoadFromFile(buttonTexture, "asset/UI/PNG/grey_button15.png");
    FileManager::LoadFromFile(trackTexture, "asset/UI/PNG/grey_sliderHorizontal.png");
    FileManager::LoadFromFile(thumbTexture, "asset/UI/PNG/grey_sliderDown.png");
}

// Destructor implementation only in debug mode
#ifdef _DEBUG
UIElementManager::~UIElementManager() {
    std::cout << "UIElementManager was destroyed!" << std::endl;
}
#endif

// Add a new button with a given label, position, and text alignment
void UIElementManager::addButton(const std::string& buttonLabel, const sf::Vector2f& buttonPosition, TextAlignment alignment) {
    Button button;
    button.text.setString(buttonLabel);
    button.text.setFont(elementFont);
    button.text.setFillColor(sf::Color::Black);
    button.text.setScale({ 1.5f, 1.5f });

    button.sprite.setTexture(buttonTexture);
    button.sprite.setPosition(buttonPosition);
    button.sprite.setScale({ 1.75f, 2.75f });
    
    button.alignment = alignment;
    button.state = ElementState::Normal;

#ifdef _DEBUG
	sf::RectangleShape debugShape({ button.sprite.getGlobalBounds().width, button.sprite.getGlobalBounds().height });
	sf::RectangleShape debugText({ button.text.getGlobalBounds().width, button.text.getGlobalBounds().height });

	debugShape.setOutlineColor(sf::Color::Red);
	debugShape.setOutlineThickness(2.f);
    debugShape.setFillColor(sf::Color(155, 255, 155, 155));
    debugShape.setPosition(buttonPosition);

    debugText.setOutlineColor(sf::Color::Blue);
    debugText.setOutlineThickness(2.f);
    debugText.setFillColor(sf::Color(255, 155, 155, 155));

	switch (button.alignment) {
	case TextAlignment::Left:
		debugText.setOrigin(0, button.text.getGlobalBounds().height / 2); // Set origin to the left-center
		debugText.setPosition(button.sprite.getPosition().x, button.sprite.getPosition().y + button.sprite.getGlobalBounds().height / 2);
		break;

	case TextAlignment::Center:
		debugText.setOrigin(button.text.getGlobalBounds().width / 2, button.text.getGlobalBounds().height / 2); // Set origin to the center
        debugText.setPosition(button.sprite.getPosition().x + button.sprite.getGlobalBounds().width / 2, button.sprite.getPosition().y + button.sprite.getGlobalBounds().height / 2);
		break;

	case TextAlignment::Right:
		debugText.setOrigin(button.text.getGlobalBounds().width, button.text.getGlobalBounds().height / 2); // Set origin to the right-center
		debugText.setPosition(button.sprite.getPosition().x + button.sprite.getGlobalBounds().width, button.sprite.getPosition().y + button.sprite.getGlobalBounds().height / 2);
		break;
	}

    debugRectangle[numberOfElements] = debugShape;
    debugTextRectangle[numberOfElements] = debugText;
#endif

    // Add button to map
    buttons[numberOfElements] = button;

    // Set button text alignment (if needed)
    updateTextPosition(numberOfElements);
    // Increment the number of elements
    numberOfElements++;
}

// Add a new buttons with a given label, position, and text alignment for many buttons
void UIElementManager::addButton(const std::vector<std::pair<std::string, sf::Vector2f>>& buttons, TextAlignment alignment) {
    for (const auto& btn : buttons) {
        addButton(btn.first, btn.second, alignment);
    }
}


// Add a new slider with a given label, position, and size
void UIElementManager::addSlider(const std::string& sliderLabel, const sf::Vector2f& sliderPosition, const sf::Vector2f& sliderSize) {
    Slider slider;
    slider.label.setFont(elementFont);
    slider.label.setString(sliderLabel);
    slider.label.setPosition(sliderPosition.x, sliderPosition.y - 50);

    slider.track.setTexture(trackTexture);
    slider.track.setPosition(sliderPosition);
    slider.track.setScale({ 3.f, 3.f });

    slider.thumb.setTexture(thumbTexture);
    slider.thumb.setPosition({ sliderPosition.x, sliderPosition.y - 10 });
    slider.state = ElementState::Normal;

    // Add slider to map
    sliders[numberOfElements] = slider;
    numberOfElements++;
}

// Set the position of an element by its ID
void UIElementManager::setPosition(unsigned short elementId, const sf::Vector2f& position) {
    if (buttons.find(elementId) != buttons.end()) {
        buttons[elementId].sprite.setPosition(position);
		updateTextPosition(elementId);
    }
    else if (sliders.find(elementId) != sliders.end()) {
        sliders[elementId].track.setPosition(position);
        sliders[elementId].thumb.setPosition(position);
        sliders[elementId].label.setPosition(position.x, position.y - 20);
    }
}

// Set the color of an element by its ID and state
void UIElementManager::setColor(unsigned short elementId, ElementState state) {
    if (buttons.find(elementId) != buttons.end()) {
        buttons[elementId].state = state;
        switch (state) {
        case ElementState::Normal:
            buttons[elementId].sprite.setColor(NORMAL_COLOR);
            break;
        case ElementState::Hovered:
            buttons[elementId].sprite.setColor(HOVER_COLOR);
            break;
        case ElementState::Pressed:
            buttons[elementId].sprite.setColor(PRESSED_COLOR);
            break;
        }
    }
    else if (sliders.find(elementId) != sliders.end()) {
        sliders[elementId].state = state;
        switch (state) {
        case ElementState::Normal:
            sliders[elementId].track.setColor(NORMAL_COLOR);
            sliders[elementId].thumb.setColor(NORMAL_COLOR);
            break;
        case ElementState::Hovered:
            sliders[elementId].track.setColor(HOVER_COLOR);
            sliders[elementId].thumb.setColor(HOVER_COLOR);
            break;
        case ElementState::Pressed:
            sliders[elementId].track.setColor(PRESSED_COLOR);
            sliders[elementId].thumb.setColor(PRESSED_COLOR);
            break;
        }
    }
}

// Check if any element is being hovered and update states
void UIElementManager::updateHover() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*windowInstance);
    sf::Vector2f mousePositionF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

    for (auto& [id, button] : buttons) {
        sf::FloatRect bounds = button.sprite.getGlobalBounds();
        if (bounds.contains(mousePositionF)) {
            setColor(id, ElementState::Hovered);
        }
        else {
            setColor(id, ElementState::Normal);
        }
    }

    for (auto& [id, slider] : sliders) {
        sf::FloatRect bounds = slider.thumb.getGlobalBounds();
        if (bounds.contains(mousePositionF)) {
            setColor(id, ElementState::Hovered);
        }
        else {
            setColor(id, ElementState::Normal);
        }
    }
}

// Get the ID of the element being hovered (-1 if none)
int UIElementManager::whichElementHover() const {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*windowInstance);
    sf::Vector2f mousePositionF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

    for (const auto& [id, button] : buttons) {
        sf::FloatRect bounds = button.sprite.getGlobalBounds();
        if (bounds.contains(mousePositionF)) {
            return static_cast<int>(id);
        }
    }

    for (const auto& [id, slider] : sliders) {
        sf::FloatRect bounds = slider.track.getGlobalBounds();
        if (bounds.contains(mousePositionF)) {
            return static_cast<int>(id);
        }
    }

    return -1;
}

// Update and render the elements
void UIElementManager::update() {
    // This function iterates through the UI elements managed by the class and draws them to the window.

    // Draw buttons
    for (const auto& [id, button] : buttons) {
        // Draw the button's sprite
        windowInstance->draw(button.sprite);
        // Draw the button's text
        windowInstance->draw(button.text);
    }

    // Draw sliders
    for (const auto& [id, slider] : sliders) {
        // Draw the slider's track
        windowInstance->draw(slider.track);
        // Draw the slider's thumb
        windowInstance->draw(slider.thumb);
        // Draw the slider's label
        windowInstance->draw(slider.label);
    }

// Draw debug UI elements (only in debug mode)
#ifdef _DEBUG
    for (const auto& [id, debugButtons] : debugRectangle) {
        windowInstance->draw(debugButtons);
    }
    for (const auto& [id, debugText] : debugTextRectangle) {
        windowInstance->draw(debugText);
    }
#endif
}

// Update text position based on element type and alignment
void UIElementManager::updateTextPosition(unsigned short elementId) {
    // This function updates the position of the text element associated with a UI element (button in this case) based on its alignment.
    if (buttons.find(elementId) != buttons.end()) {
        auto& button = buttons[elementId];
        sf::FloatRect textBounds = button.text.getGlobalBounds();
        sf::FloatRect spriteBounds = button.sprite.getGlobalBounds();
        sf::Vector2f position = button.sprite.getPosition();

        switch (button.alignment) {
        case TextAlignment::Left:
            // Align text to the left of the button's sprite
            button.text.setPosition(position.x, position.y + spriteBounds.height / 3.5f - textBounds.height / 3.5f);
            break;
        case TextAlignment::Center:
            // Align text centered horizontally within the button's sprite
            button.text.setPosition(
            position.x + spriteBounds.width / 2.f - textBounds.width / 2.f,
            position.y + spriteBounds.height / 3.5f - textBounds.height / 3.5f
            );
            break;
        case TextAlignment::Right:
            // Align text to the right of the button's sprite
            button.text.setPosition(position.x + spriteBounds.width - textBounds.width, position.y + spriteBounds.height / 3.5f - textBounds.height / 3.5f);
            break;
        }
    }
}
