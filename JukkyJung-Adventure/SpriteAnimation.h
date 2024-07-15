#pragma once
#include "common.h"

// SpriteAnimation class is responsible for managing and displaying sprite animations
class SpriteAnimation {
public:
    // Constructor to initialize the SpriteAnimation with a pointer to the SFML render window
    SpriteAnimation(sf::RenderWindow* window);

    /**
     * Loads animation frames from a sprite sheet with multiple rows and columns.
     * @param filePath Path to the sprite sheet image
     * @param spriteName Name of the sprite
     * @param frameSize Size of each frame in the sprite sheet
     * @param rowCount Number of rows in the sprite sheet
     * @param position Initial position of the sprite (default: {0, 0})
     */
    void loadSpriteSheet(const std::string& filePath, const std::string& spriteName, sf::Vector2i frameSize, uint64_t rowCount, sf::Vector2f position = {0, 0});

    /**
     * Sets the scale of the sprite.
     * @param spriteName Name of the sprite
     * @param scale Scale vector (x, y) for the sprite
     */
    void setScale(const std::string& spriteName, const sf::Vector2f& scale);

    /**
     * Sets the current state (row) of the animation.
     * @param spriteName Name of the sprite
     * @param stateName Name of the animation state
     * @param startRow Row index of the animation in the sprite sheet
     * @param frameCount Number of frames in the animation
     * @param duration Duration of each frame
     */
    void setState(const std::string& spriteName, const std::string& stateName, uint64_t startRow, uint64_t frameCount, float duration);

    /**
     * Sets the current state (row and column range) of the animation.
     * @param spriteName Name of the sprite
     * @param stateName Name of the animation state
     * @param startRow Row index of the animation in the sprite sheet
     * @param startCol Starting column index of the animation
     * @param endCol Ending column index of the animation
     * @param duration Duration of each frame
     */
    void setState(const std::string& spriteName, const std::string& stateName, uint64_t startRow, uint64_t startCol, uint64_t endCol, float duration);

    /**
     * Changes to a different state.
     * @param spriteName Name of the sprite
     * @param stateName Name of the new state
     * @param resetCurrentFrame Flag to reset the current frame to the first frame of the new state (default: false)
     */
    void changeState(const std::string& spriteName, const std::string& stateName, bool resetCurrentFrame = false);

    sf::Vector2f getPosition(const std::string& spriteName);

    /**
     * Moves the sprite by a given offset.
     * @param spriteName Name of the sprite
     * @param offset Offset vector (x, y) to move the sprite
     */
    void moveSprite(const std::string& spriteName, sf::Vector2f offset);

    const sf::Sprite& getSprite(const std::string& spriteName) const;

    /**
     * Updates the animation frame based on elapsed time.
     * @param spriteName Name of the sprite
     * @param deltaTime Time elapsed since the last frame update
     */
    void updateAnimation(const std::string& spriteName, float deltaTime);

    /**
     * Draws the current frame of the animation.
     * @param spriteName Name of the sprite
     */
    void drawAnimation(const std::string& spriteName);

private:
    // Structure to hold information about an animation state
    struct AnimationState {
        std::vector<sf::IntRect> frames;  // Frames of the animation
        uint64_t currentFrame;            // Current frame being displayed
        float duration;                   // Duration of each frame
        float elapsedTime;                // Time elapsed since the last frame change

        AnimationState() : currentFrame(0), duration(0), elapsedTime(0) {}
    };

    // Structure to hold information about an animation sprite
    struct AnimationSprite {
        sf::Texture texture;                                     // Texture of the sprite sheet
        sf::Sprite sprite;                                       // Sprite to display the current frame
        sf::Vector2i frameSize;                                  // Size of each frame
        uint64_t rowCount;                                       // Number of rows in the sprite sheet

        std::unordered_map<std::string, AnimationState> states;  // Map of state names to animation states
        AnimationState* currentState;                            // Pointer to the current animation state

        AnimationSprite() : rowCount(0), currentState(nullptr) {}
    };

    sf::RenderWindow* windowInstance;  // Pointer to the SFML render window

    std::unordered_map<std::string, std::shared_ptr<AnimationSprite>> animationSprites;  // Map of sprite names to their AnimationSprite

#ifdef _DEBUG
    std::map<std::string, sf::RectangleShape> debugShape;  // Debug shape to visualize the sprite boundaries in debug mode
#endif
};
