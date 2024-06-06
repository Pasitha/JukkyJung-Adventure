#include "SpriteAnimation.h"

// Constructor
SpriteAnimation::SpriteAnimation(sf::RenderWindow* window) : windowInstance(window), currentState(nullptr) {}

// Load animation frames from a sprite sheet with multiple rows and columns
void SpriteAnimation::loadSpriteSheet(const std::string& filePath, sf::Vector2i frameSize, int rowCount, sf::Vector2f position) {
    this->frameSize = frameSize;
    this->rowCount = rowCount;

    // Load the texture from file
    FileManager::LoadFromFile(texture, filePath);
    sprite.setTexture(texture);
    sprite.setPosition(position);

#ifdef _DEBUG
    // Create a debug shape to visualize the sprite bounds (optional)
    debugShape.setSize((sf::Vector2f)frameSize);
    debugShape.setPosition(position);

    std::cout << sprite.getGlobalBounds().width << " " << sprite.getGlobalBounds().height << std::endl;

    // Set debug shape properties
    debugShape.setOutlineColor(sf::Color::Red);
    debugShape.setOutlineThickness(2.f);
    debugShape.setFillColor(sf::Color(155, 255, 155, 55));
#endif
}

// Set the scale of the sprite
void SpriteAnimation::setScale(const sf::Vector2f& scale) {
    sprite.setScale(scale);

#ifdef _DEBUG
    // Update debug shape size when scaling the sprite
    debugShape.setSize({ debugShape.getSize().x * scale.x, debugShape.getSize().y * scale.y });
#endif
}

// Set the current state (row) of the animation
void SpriteAnimation::setState(const std::string& stateName, int startRow, int frameCount, float duration) {
    AnimationState state;
    state.duration = duration;

    // Generate frames for the specified state by creating IntRects for each frame
    for (int i = 0; i < frameCount; ++i) {
        state.frames.emplace_back(i * frameSize.x, startRow * frameSize.y, frameSize.x, frameSize.y);
    }

    // Add the state to the map of states
    states[stateName] = state;

    // Set the current state if it's the first state being added
    if (currentState == nullptr) {
        currentState = &states[stateName];
    }
}

// Change to a different state
void SpriteAnimation::changeState(const std::string& stateName) {
    auto it = states.find(stateName);
    if (it != states.end()) {
        currentState = &it->second;
        currentState->currentFrame = 0; // Reset the current frame when switching states
    } else {
        throw std::runtime_error("State not found: " + stateName);
    }
}

// Move the sprite by a given offset
void SpriteAnimation::moveSprite(sf::Vector2f offset) {
    sprite.move(offset);

#ifdef _DEBUG
    // Update debug shape position when moving the sprite
    debugShape.move(offset);
#endif
}

// Update the animation frame based on elapsed time
void SpriteAnimation::updateAnimation(float deltaTime) {
    if (currentState) {
        // Update elapsed time for the current animation state
        currentState->elapsedTime += deltaTime;

        // Check if it's time to switch to the next frame
        if (currentState->elapsedTime >= currentState->duration) {
        // Reset elapsed time
        currentState->elapsedTime -= currentState->duration;

        // Move to the next frame, looping back to the first frame if necessary
        currentState->currentFrame = (currentState->currentFrame + 1) % currentState->frames.size();
        }

        // Set the current frame texture rectangle for the sprite
        sprite.setTextureRect(currentState->frames[currentState->currentFrame]);
    }
}

// Draw the current frame of the animation
void SpriteAnimation::drawAnimation() {
    windowInstance->draw(sprite);

#ifdef _DEBUG
    // Optionally draw the debug shape to visualize the sprite bounds
    windowInstance->draw(debugShape);
#endif
}
