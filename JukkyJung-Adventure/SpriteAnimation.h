#pragma once
#include "common.h"

// SpriteAnimation class is responsible for managing and displaying sprite animations
class SpriteAnimation {
public:
    // Constructor taking a pointer to the SFML render window
    SpriteAnimation(sf::RenderWindow* window);

    // Load animation frames from a sprite sheet with multiple rows and columns
    void loadSpriteSheet(const std::string& filePath, const std::string& spriteName, sf::Vector2i frameSize, int rowCount, sf::Vector2f position = { 0, 0 });

    // Set the scale of the sprite
    void setScale(const std::string& spriteName, const sf::Vector2f& scale);

    // Set the current state (row) of the animation
    void setState(const std::string& spriteName, const std::string& stateName, int startRow, int frameCount, float duration);

    // Change to a different state
    void changeState(const std::string& spriteName, const std::string& stateName, bool resetCurrentFrame = false);

    // Move the sprite by a given offset
    void moveSprite(const std::string& spriteName, sf::Vector2f offset);

    // Update the animation frame based on elapsed time
    void updateAnimation(const std::string& spriteName, float deltaTime);

    // Draw the current frame
    void drawAnimation(const std::string& spriteName);

private:
    // Structure to hold information about an animation state
    struct AnimationState {
        std::vector<sf::IntRect> frames;  // Frames of the animation
        int currentFrame;                 // Current frame being displayed
        float duration;                   // Duration of each frame
        float elapsedTime;                // Time elapsed since the last frame change

        AnimationState() : currentFrame(0), duration(0), elapsedTime(0) {}
    };

    struct AnimationSprite {
		sf::Texture texture;                                     // Texture of the sprite sheet
		sf::Sprite sprite;                                       // Sprite to display the current frame
		sf::Vector2i frameSize;                                  // Size of each frame
		int rowCount;                                            // Number of rows in the sprite sheet

		std::unordered_map<std::string, AnimationState> states;  // Map of state names to animation states
		AnimationState* currentState;                            // Pointer to the current animation state

        AnimationSprite() : rowCount(0), currentState(nullptr) {}
    };

	// Pointer to the SFML render window
    sf::RenderWindow* windowInstance;

    std::unordered_map<std::string, std::shared_ptr<AnimationSprite>> animationSprite;

#ifdef _DEBUG
    // Debug shape to visualize the sprite boundaries in debug mode
    std::map<std::string, sf::RectangleShape> debugShape;
#endif
};
