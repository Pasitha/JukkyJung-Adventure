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
    // Create a new button instance
    Button button;

    // Set button text properties
    button.text.setString(buttonLabel);
    button.text.setFont(elementFont);
    button.text.setFillColor(sf::Color::Black);
    button.text.setScale({ 1.5f, 1.5f });

    // Set button sprite properties
    button.sprite.setTexture(buttonTexture);
    button.sprite.setPosition(buttonPosition);
    button.sprite.setScale({ 1.75f, 2.75f });

    // Set button alignment and initial state
    button.alignment = alignment;
    button.state = ElementState::Normal;

    // Add debug UI elements in debug mode (optional)
#ifdef _DEBUG
    // Create debug shapes for the button and its text
    sf::RectangleShape debugShape({ button.sprite.getGlobalBounds().width, button.sprite.getGlobalBounds().height });
    sf::RectangleShape debugText({ button.text.getGlobalBounds().width, button.text.getGlobalBounds().height });

    // Set debug shape properties
    debugShape.setOutlineColor(sf::Color::Red);
    debugShape.setOutlineThickness(2.f);
    debugShape.setFillColor(sf::Color(155, 255, 155, 155));
    debugShape.setPosition(buttonPosition);

    // Set debug text properties
    debugText.setOutlineColor(sf::Color::Blue);
    debugText.setOutlineThickness(2.f);
    debugText.setFillColor(sf::Color(255, 155, 155, 155));

    // Set debug text origin based on alignment
    switch (button.alignment) {
        case TextAlignment::Left:
            debugText.setOrigin(0, button.text.getGlobalBounds().height / 2);
            debugText.setPosition(button.sprite.getPosition().x, button.sprite.getPosition().y + button.sprite.getGlobalBounds().height / 2);
            break;
        case TextAlignment::Center:
            debugText.setOrigin(button.text.getGlobalBounds().width / 2, button.text.getGlobalBounds().height / 2);
            debugText.setPosition(button.sprite.getPosition().x + button.sprite.getGlobalBounds().width / 2, button.sprite.getPosition().y + button.sprite.getGlobalBounds().height / 2);
            break;
        case TextAlignment::Right:
            debugText.setOrigin(button.text.getGlobalBounds().width, button.text.getGlobalBounds().height / 2);
            debugText.setPosition(button.sprite.getPosition().x + button.sprite.getGlobalBounds().width, button.sprite.getPosition().y + button.sprite.getGlobalBounds().height / 2);
            break;
    }

    // Add debug shapes to the respective maps
    debugRectangle[numberOfElements] = debugShape;
    debugTextRectangle[numberOfElements] = debugText;
#endif

    // Add the button to the buttons map with a unique ID (numberOfElements)
    buttons[numberOfElements] = button;

    // Update the text position based on alignment (if needed)
    updateTextPosition(static_cast<uint16_t>(numberOfElements));

    // Increment the counter for the number of elements
    numberOfElements++;
}

// Add new buttons with given labels, positions, and text alignment for multiple buttons
void UIElementManager::addButton(const std::vector<std::pair<std::string, sf::Vector2f>>& buttons, TextAlignment alignment) {
    // Iterate through each button and add it using the addButton method
    for (const auto& btn : buttons) {
        addButton(btn.first, btn.second, alignment);
    }
}

// Add a new slider with a given label and position
void UIElementManager::addSlider(const std::string& sliderLabel, const sf::Vector2f& sliderPosition) {
    // Create a new slider instance
    Slider slider;

    // Set slider label properties
    slider.label.setFont(elementFont);
    slider.label.setString(sliderLabel);
    slider.label.setPosition(sliderPosition.x, sliderPosition.y - 50);

    // Set slider track properties
    slider.track.setTexture(trackTexture);
    slider.track.setPosition(sliderPosition);
    slider.track.setScale({ 3.f, 3.f });

    // Set slider thumb properties
    slider.thumb.setTexture(thumbTexture);
    slider.thumb.setPosition({ sliderPosition.x, sliderPosition.y - 10 });
    slider.state = ElementState::Normal;

    // Add slider to map
    sliders[numberOfElements] = slider;

    // Increment the counter for the number of elements
    numberOfElements++;
}

// Set the position of an element by its ID
void UIElementManager::setPosition(uint64_t elementId, const sf::Vector2f& position) {
    // Check if the element is a button and set its position
    if (buttons.find(elementId) != buttons.end()) {
        buttons[elementId].sprite.setPosition(position);
        updateTextPosition(elementId);
    }
    // Check if the element is a slider and set its position
    else if (sliders.find(elementId) != sliders.end()) {
        sliders[elementId].track.setPosition(position);
        sliders[elementId].thumb.setPosition(position.x, position.y - 10);
        sliders[elementId].label.setPosition(position.x, position.y - 50);
    }
}

// Set the thumb position of a slider by its ID
void UIElementManager::setThumbPosition(uint64_t elementId) {
    // Check if the element is a slider and set its thumb position based on mouse position
    if (sliders.find(elementId) != sliders.end()) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(*windowInstance);
        sf::Vector2f mousePositionF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
        sliders[elementId].thumb.setPosition(std::max(sliders[elementId].track.getGlobalBounds().width, mousePositionF.x), sliders[elementId].thumb.getPosition().y);
    }
}

// Set the color of an element by its ID and state
void UIElementManager::setColor(uint64_t elementId, ElementState state) {
    // Check if the element is a button and set its color based on state
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
    // Check if the element is a slider and set its color based on state
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
    // Get the current mouse position in the window
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*windowInstance);
    sf::Vector2f mousePositionF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

    // Update hover state for buttons
    for (auto& [id, button] : buttons) {
        sf::FloatRect bounds = button.sprite.getGlobalBounds();
        if (bounds.contains(mousePositionF)) {
            setColor(static_cast<uint16_t>(id), ElementState::Hovered);
        } else {
            setColor(static_cast<uint16_t>(id), ElementState::Normal);
        }
    }

    // Update hover state for sliders
    for (auto& [id, slider] : sliders) {
        sf::FloatRect bounds = slider.track.getGlobalBounds();
        if (bounds.contains(mousePositionF)) {
            setColor(static_cast<uint16_t>(id), ElementState::Hovered);
        } else {
            setColor(static_cast<uint16_t>(id), ElementState::Normal);
        }
    }
}

// Get the ID of the element being hovered (-1 if none)
int UIElementManager::whichElementHover() const {
    // Get the current mouse position in the window
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*windowInstance);
    sf::Vector2f mousePositionF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

    // Check if a button is being hovered and return its ID
    for (const auto& [id, button] : buttons) {
        sf::FloatRect bounds = button.sprite.getGlobalBounds();
        if (bounds.contains(mousePositionF)) {
            return static_cast<int>(id);
        }
    }

    // Check if a slider is being hovered and return its ID
    for (const auto& [id, slider] : sliders) {
        sf::FloatRect bounds = slider.track.getGlobalBounds();
        if (bounds.contains(mousePositionF)) {
            return static_cast<int>(id);
        }
    }

    // Return -1 if no element is being hovered
    return -1;
}

// Update and render the elements
void UIElementManager::update() {
    // Draw buttons
    for (const auto& [id, button] : buttons) {
        windowInstance->draw(button.sprite);
        windowInstance->draw(button.text);
    }

    // Draw sliders
    for (const auto& [id, slider] : sliders) {
        windowInstance->draw(slider.track);
        windowInstance->draw(slider.thumb);
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
void UIElementManager::updateTextPosition(uint64_t elementId) {
    // Check if the element is a button
    if (buttons.find(elementId) != buttons.end()) {
        auto& button = buttons[elementId];

        sf::FloatRect textBounds = button.text.getGlobalBounds();
        sf::FloatRect spriteBounds = button.sprite.getGlobalBounds();

        sf::Vector2f position = button.sprite.getPosition();

        // Update the text position based on alignment
        switch (button.alignment) {
            case TextAlignment::Left:
                button.text.setPosition(position.x, position.y + spriteBounds.height / 3.5f - textBounds.height / 3.5f);
                break;
            case TextAlignment::Center:
                button.text.setPosition(position.x + spriteBounds.width / 2.f - textBounds.width / 2.f, position.y + spriteBounds.height / 3.5f - textBounds.height / 3.5f);
                break;
            case TextAlignment::Right:
                button.text.setPosition(position.x + spriteBounds.width - textBounds.width, position.y + spriteBounds.height / 3.5f - textBounds.height / 3.5f);
                break;
        }
    }
}
