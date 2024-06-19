#pragma once
#include "common.h"

// Forward declarations for classes used in UIElementManager
class sf::RenderWindow;

// Enumeration for text alignment options
enum class TextAlignment { Left, Center, Right };

// Enumeration for element states
enum class ElementState { Normal, Hovered, Pressed };

// UIElementManager class is responsible for managing UI elements
class UIElementManager {
public:
    // Constructor to initialize the UIElementManager with a pointer to the SFML window
    UIElementManager(sf::RenderWindow* window);
    
#ifdef _DEBUG
    // Destructor added only in debug mode as a reminder for cleanup
    ~UIElementManager();
#endif

    /**
     * Adds a new button with the specified label, position, and text alignment.
     * @param buttonLabel Label of the button
     * @param buttonPosition Position of the button
     * @param alignment Text alignment for the button (default: Center)
     */
    void addButton(const std::string& buttonLabel, const sf::Vector2f& buttonPosition, TextAlignment alignment = TextAlignment::Center);
    
    /**
     * Adds multiple buttons with the specified labels and positions.
     * @param buttons Vector of pairs containing button labels and positions
     * @param alignment Text alignment for the buttons (default: Center)
     */
    void addButton(const std::vector<std::pair<std::string, sf::Vector2f>>& buttons, TextAlignment alignment = TextAlignment::Center);

    /**
     * Adds a new slider with the specified label and position.
     * @param sliderLabel Label of the slider
     * @param sliderPosition Position of the slider
     */
    void addSlider(const std::string& sliderLabel, const sf::Vector2f& sliderPosition);

    /**
     * Sets the position of an element by its ID.
     * @param elementId ID of the element
     * @param position New position of the element
     */
    void setPosition(uint16_t elementId, const sf::Vector2f& position);

	/**
     * Sets the thumb position for a slider by its ID.
     * @param elementId ID of the element
     */
    void setThumbPosition(uint16_t elementId);

    /**
     * Sets the color of an element by its ID and state.
     * @param elementId ID of the element
     * @param state State of the element (Normal, Hovered, Pressed)
     */
    void setColor(uint16_t elementId, ElementState state);

    // Updates hover states for elements based on mouse position
    void updateHover();

    /**
     * Gets the ID of the element being hovered.
     * @return ID of the hovered element, or -1 if none
     */
    int whichElementHover() const;

    // Updates and renders the elements
    void update();

private:
    /**
     * Updates text position based on element type and alignment.
     * @param elementId ID of the element
     */
    void updateTextPosition(uint16_t elementId);

    // Struct representing a button element
    struct Button {
        sf::Sprite sprite;           // Sprite for the button
        sf::Text text;               // Text for the button
        TextAlignment alignment;     // Text alignment for the button
        ElementState state;          // State of the button
    };

    // Struct representing a slider element
    struct Slider {
        sf::Sprite track;            // Sprite for the slider track
        sf::Sprite thumb;            // Sprite for the slider thumb
        sf::Text label;              // Label for the slider
        ElementState state;          // State of the slider
    };

    // Constants for element colors
    static const sf::Color NORMAL_COLOR;
    static const sf::Color HOVER_COLOR;
    static const sf::Color PRESSED_COLOR;

    // Alpha values for color transparency
    static const int COLOR_ALPHA_NORMAL = 255;
    static const int COLOR_ALPHA_HOVER = 155;
    static const int COLOR_ALPHA_PRESSED = 100;

    size_t numberOfElements;           // Number of elements managed

    sf::RenderWindow* windowInstance;  // Pointer to the SFML render window

    sf::Font elementFont;              // Font for element text
    sf::Texture buttonTexture;         // Texture for buttons
    sf::Texture trackTexture;          // Texture for slider tracks
    sf::Texture thumbTexture;          // Texture for slider thumbs
    
    std::map<size_t, Button> buttons;  // Map of button elements
    std::map<size_t, Slider> sliders;  // Map of slider elements

#ifdef _DEBUG
    std::map<size_t, sf::RectangleShape> debugRectangle;      // Debug rectangles for buttons
    std::map<size_t, sf::RectangleShape> debugTextRectangle;  // Debug rectangles for text
#endif
};
