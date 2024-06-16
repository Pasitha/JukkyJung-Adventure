#include "SpriteAnimation.h"

// Constructor
SpriteAnimation::SpriteAnimation(sf::RenderWindow* window) : windowInstance(window) {}

// Load animation frames from a sprite sheet with multiple rows and columns
void SpriteAnimation::loadSpriteSheet(const std::string& filePath, const std::string& spriteName, sf::Vector2i frameSize, uint64_t rowCount, sf::Vector2f position) {
    std::shared_ptr<AnimationSprite> Sprite = std::make_shared<AnimationSprite>();
    // Load the texture from file
    if (FileManager::LoadFromFile(Sprite->texture, filePath)) {
#ifdef _DEBUG
        std::cout << "load " + filePath + " complete" << std::endl;
#endif
    }

    Sprite->frameSize = frameSize;
    Sprite->rowCount = rowCount;
    Sprite->sprite.setTexture(Sprite->texture);
    Sprite->sprite.setPosition(position);

    animationSprites[spriteName] = Sprite;

#ifdef _DEBUG
    // Create a debug shape to visualize the sprite bounds (optional)
    debugShape[spriteName].setSize((sf::Vector2f)frameSize);
    debugShape[spriteName].setPosition(position);

    std::cout << Sprite->sprite.getGlobalBounds().width << " " << Sprite->sprite.getGlobalBounds().height << std::endl;

    // Set debug shape properties
    debugShape[spriteName].setOutlineColor(sf::Color::Red);
    debugShape[spriteName].setOutlineThickness(2.f);
    debugShape[spriteName].setFillColor(sf::Color(155, 255, 155, 55));
#endif
}

// Set the scale of the sprite
void SpriteAnimation::setScale(const std::string& spriteName, const sf::Vector2f& scale) {
    animationSprites[spriteName]->sprite.setScale(scale);

#ifdef _DEBUG
    // Update debug shape size when scaling the sprite
    debugShape[spriteName].setSize({ debugShape[spriteName].getSize().x * scale.x, debugShape[spriteName].getSize().y * scale.y });
#endif
}

// Set the current state (row) of the animation
void SpriteAnimation::setState(const std::string& spriteName, const std::string& stateName, uint64_t startRow, uint64_t frameCount, float duration) {
    AnimationState state;
    state.duration = duration;

    // Generate frames for the specified state by creating IntRects for each frame
    for (uint64_t col = 0; col < frameCount; col++) {
#ifdef _DEBUG
        std::cout << "setState for startRow: " << startRow << ", to " << frameCount << " ( " << col << " )" << std::endl;
#endif
        state.frames.emplace_back(
            col * animationSprites[spriteName]->frameSize.x, startRow * animationSprites[spriteName]->frameSize.y, 
            animationSprites[spriteName]->frameSize.x, animationSprites[spriteName]->frameSize.y
        );
    }

    // Add the state to the map of states
    animationSprites[spriteName]->states[stateName] = state;

    // Set the current state if it's the first state being added
    if (animationSprites[spriteName]->currentState == nullptr) {
        animationSprites[spriteName]->currentState = &animationSprites[spriteName]->states[stateName];
    }
}

// Set the current state (row) of the animation
void SpriteAnimation::setState(const std::string& spriteName, const std::string& stateName, uint64_t startRow, uint64_t startCol, uint64_t endCol, float duration) {
    AnimationState state;
    state.duration = duration;

    // Generate frames for the specified state by creating IntRects for each frame
    for (uint64_t col = startCol; col <= endCol; col++) {
        state.frames.emplace_back(
            col * animationSprites[spriteName]->frameSize.x, startRow * animationSprites[spriteName]->frameSize.y,
            animationSprites[spriteName]->frameSize.x, animationSprites[spriteName]->frameSize.y
        );
    }

    // Add the state to the map of states
    animationSprites[spriteName]->states[stateName] = state;

    // Set the current state if it's the first state being added
    if (animationSprites[spriteName]->currentState == nullptr) {
        animationSprites[spriteName]->currentState = &animationSprites[spriteName]->states[stateName];
    }
}

// Change to a different state
void SpriteAnimation::changeState(const std::string& spriteName, const std::string& stateName, bool resetCurrentFrame) {
    // Find the new state in the map
    auto it = animationSprites[spriteName]->states.find(stateName);
    if (it != animationSprites[spriteName]->states.end()) {
        // Save the current frame from the current state
        uint64_t currentFrame = animationSprites[spriteName]->currentState->currentFrame;
        // Update the current state to the new state
        animationSprites[spriteName]->currentState = &it->second;
        // Retain the current frame if not resetting
        animationSprites[spriteName]->currentState->currentFrame = currentFrame;
        // Reset the current frame to the first frame if specified
        if (resetCurrentFrame) {
            animationSprites[spriteName]->currentState->currentFrame = 0;
        }
    } else {
        // Throw an error if the state is not found
        throw std::runtime_error("State not found: " + stateName);
    }
}

// Move the sprite by a given offset
void SpriteAnimation::moveSprite(const std::string& spriteName, sf::Vector2f offset) {
    animationSprites[spriteName]->sprite.move(offset);

#ifdef _DEBUG
    // Update debug shape position when moving the sprite
    debugShape[spriteName].move(offset);
#endif
}

// Update the animation frame based on elapsed time
void SpriteAnimation::updateAnimation(const std::string& spriteName, float deltaTime) {
    if (animationSprites[spriteName]->currentState) {
        // Update elapsed time for the current animation state
        animationSprites[spriteName]->currentState->elapsedTime += deltaTime;

        // Check if it's time to switch to the next frame
        if (animationSprites[spriteName]->currentState->elapsedTime >= animationSprites[spriteName]->currentState->duration) {
            // Reset elapsed time
            animationSprites[spriteName]->currentState->elapsedTime -= animationSprites[spriteName]->currentState->duration;

            // Move to the next frame, looping back to the first frame if necessary
            animationSprites[spriteName]->currentState->currentFrame = (animationSprites[spriteName]->currentState->currentFrame) + 1 % animationSprites[spriteName]->currentState->frames.size();
        }

        // Set the current frame texture rectangle for the sprite
        animationSprites[spriteName]->sprite.setTextureRect(animationSprites[spriteName]->currentState->frames[animationSprites[spriteName]->currentState->currentFrame]);
    }
}

// Draw the current frame of the animation
void SpriteAnimation::drawAnimation(const std::string& spriteName) {
    windowInstance->draw(animationSprites[spriteName]->sprite);

#ifdef _DEBUG
    // Optionally draw the debug shape to visualize the sprite bounds
    windowInstance->draw(debugShape[spriteName]);
#endif
}
