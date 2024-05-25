#pragma once
#include "common.h"

// Forward declarations for classes used in UIElementManager
class sf::RenderWindow;

// Text alignment options
enum class TextAlignment { Left, Center, Right };

// Element state
enum class ElementState { Normal, Hovered, Pressed };

// UIElementManager class is responsible for managing UI elements
class UIElementManager {
public:
	// Constructor and destructor
	UIElementManager(sf::RenderWindow* window);
#ifdef _DEBUG
	~UIElementManager();
#endif

	// Add a new button with a given label, position, and text alignment
	void addButton(const std::string& buttonLabel, const sf::Vector2f& buttonPosition, TextAlignment alignment = TextAlignment::Center);

	// Add a new slider with a given label, position, and size
	void addSlider(const std::string& sliderLabel, const sf::Vector2f& sliderPosition, const sf::Vector2f& sliderSize);

	// Set the position of an element by its ID
	void setPosition(unsigned short elementId, const sf::Vector2f& position);

	// Set the color of an element by its ID and state
	void setColor(unsigned short elementId, ElementState state);

	// Check if any element is being hovered and update states
	void updateHover();

	// Get the ID of the element being hovered (-1 if none)
	int whichElementHover() const;

	// Update and render the elements
	void update();

private:
	// Update text position based on element type and alignment
	void updateTextPosition(unsigned short elementId);

	// Constants for element colors
	static const sf::Color NORMAL_COLOR;
	static const sf::Color HOVER_COLOR;
	static const sf::Color PRESSED_COLOR;  // New for pressed state

	// Alpha values for color transparency
	static const int COLOR_ALPHA_NORMAL = 255;
	static const int COLOR_ALPHA_HOVER = 155;
	static const int COLOR_ALPHA_PRESSED = 100;  // New for pressed state

	// Number of elements
	size_t numberOfElements;

	// Pointer to the SFML render window
	sf::RenderWindow* windowInstance;

	// SFML font, texture (optional for buttons), sprite (optional for buttons), and text
	sf::Font elementFont;
	sf::Texture elementTexture;  // Optional for buttons
	sf::Sprite elementSprite;    // Optional for buttons
	sf::Text elementText;

	// Map to associate element IDs with their components (Sprite, Text)
	std::map<size_t, std::pair<sf::Sprite, sf::Text>> elementComponents;

	// Map to associate element IDs with their types and alignment
	std::map<size_t, std::pair<std::string, TextAlignment>> elementInfo;

	// Map to associate element IDs with their state
	std::map<size_t, ElementState> elementStates;

	// Slider specific components
	std::map<size_t, sf::RectangleShape> sliders;
};