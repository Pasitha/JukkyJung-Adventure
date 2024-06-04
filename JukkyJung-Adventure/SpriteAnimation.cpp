#include "SpriteAnimation.h"

// Constructor
SpriteAnimation::SpriteAnimation(sf::RenderWindow* window) : windowInstance(window), currentState(nullptr) {}

// Load animation frames from a sprite sheet with multiple rows and columns
void SpriteAnimation::loadSpriteSheet(const std::string& filePath, sf::Vector2i frameSize, int rowCount) {
    this->frameSize = frameSize;
    this->rowCount = rowCount;

    // Load the texture from file
    FileManager::LoadFromFile(texture, filePath);
    sprite.setTexture(texture);
}

void SpriteAnimation::setScale(const sf::Vector2f& scale) {
    sprite.setScale(scale);
}

// Set the current state (row) of the animation
void SpriteAnimation::setState(const std::string& stateName, int startRow, int frameCount, float duration) {
    AnimationState state;
    state.duration = duration;

    // Generate frames for the specified state
    for (int i = 0; i < frameCount; ++i) {
        state.frames.emplace_back(i * frameSize.x, startRow * frameSize.y, frameSize.x, frameSize.y);
    }

    // Add the state to the map
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
        currentState->currentFrame = 0;
    }
    else {
        throw std::runtime_error("State not found: " + stateName);
    }
}

void SpriteAnimation::moveSprite(sf::Vector2f offset) {
    sprite.move(offset);
}

// Update the animation frame based on elapsed time
void SpriteAnimation::updateAnimation(float deltaTime) {
    if (currentState) {
        // Update elapsed time
        currentState->elapsedTime += deltaTime;
        if (currentState->elapsedTime >= currentState->duration) {
            // Reset elapsed time
            currentState->elapsedTime -= currentState->duration;
            // Move to the next frame
            currentState->currentFrame = (currentState->currentFrame + 1) % currentState->frames.size();
        }
        // Set the current frame to the sprite
        sprite.setTextureRect(currentState->frames[currentState->currentFrame]);
    }
}

// Draw the current frame
void SpriteAnimation::drawAnimation(sf::Vector2f position) {
    sprite.setPosition(position);
    windowInstance->draw(sprite);
}
