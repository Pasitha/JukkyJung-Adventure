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
    FileManager::LoadFromFile(thumbTexture, "asset/UI/PNG/grey_button15.png");
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
    button.text.setFont(elementFont);
    button.text.setString(buttonLabel);
    button.sprite.setTexture(buttonTexture);
    button.sprite.setPosition(buttonPosition);
    button.alignment = alignment;
    button.state = ElementState::Normal;

    button.sprite.setScale({ 1.75f, 2.75f });
    button.text.setFillColor(sf::Color::Black);
    button.text.setScale({ 1.5f, 1.5f });

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
    slider.track.setSize(sliderSize);
    slider.track.setPosition(sliderPosition);
    slider.thumb.setSize({ sliderSize.x / 10, sliderSize.y });
    slider.thumb.setPosition(sliderPosition);
    slider.label.setFont(elementFont);
    slider.label.setString(sliderLabel);
    slider.label.setPosition(sliderPosition.x, sliderPosition.y - 20);
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
            sliders[elementId].track.setFillColor(NORMAL_COLOR);
            sliders[elementId].thumb.setFillColor(NORMAL_COLOR);
            sliders[elementId].label.setFillColor(NORMAL_COLOR);
            break;
        case ElementState::Hovered:
            sliders[elementId].track.setFillColor(HOVER_COLOR);
            sliders[elementId].thumb.setFillColor(HOVER_COLOR);
            sliders[elementId].label.setFillColor(HOVER_COLOR);
            break;
        case ElementState::Pressed:
            sliders[elementId].track.setFillColor(PRESSED_COLOR);
            sliders[elementId].thumb.setFillColor(PRESSED_COLOR);
            sliders[elementId].label.setFillColor(PRESSED_COLOR);
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
        sf::FloatRect bounds = slider.track.getGlobalBounds();
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
    for (const auto& [id, button] : buttons) {
        windowInstance->draw(button.sprite);
        windowInstance->draw(button.text);
    }
    for (const auto& [id, slider] : sliders) {
        windowInstance->draw(slider.track);
        windowInstance->draw(slider.thumb);
        windowInstance->draw(slider.label);
    }
}

// Update text position based on element type and alignment
void UIElementManager::updateTextPosition(unsigned short elementId) {
    if (buttons.find(elementId) != buttons.end()) {
        auto& button = buttons[elementId];
        sf::FloatRect textBounds = button.text.getGlobalBounds();
        sf::Vector2f position = button.sprite.getPosition();
        switch (button.alignment) {
        case TextAlignment::Left:
            button.text.setPosition(position.x, position.y);
            break;
        case TextAlignment::Center:
            button.text.setOrigin(textBounds.width / 2, textBounds.height / 2);
            button.text.setPosition(
                position.x + button.sprite.getGlobalBounds().width / 2.f - textBounds.width / 2.f,
				position.y + button.sprite.getGlobalBounds().height / 3.5f - textBounds.height / 3.5f
            );
            break;
        case TextAlignment::Right:
            button.text.setPosition(
                position.x + button.sprite.getGlobalBounds().width - textBounds.width,
				position.y 
            );
            break;
        }
    }
}
