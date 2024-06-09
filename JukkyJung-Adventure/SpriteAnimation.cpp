#include "SpriteAnimation.h"

// Constructor
SpriteAnimation::SpriteAnimation(sf::RenderWindow* window) : windowInstance(window) {}

// Load animation frames from a sprite sheet with multiple rows and columns
void SpriteAnimation::loadSpriteSheet(const std::string& filePath, const std::string& spriteName, sf::Vector2i frameSize, int rowCount, sf::Vector2f position) {
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

    animationSprite[spriteName] = Sprite;

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
    animationSprite[spriteName]->sprite.setScale(scale);

#ifdef _DEBUG
    // Update debug shape size when scaling the sprite
    debugShape[spriteName].setSize({ debugShape[spriteName].getSize().x * scale.x, debugShape[spriteName].getSize().y * scale.y });
#endif
}

// Set the current state (row) of the animation
void SpriteAnimation::setState(const std::string& spriteName, const std::string& stateName, int startRow, int frameCount, float duration) {
    AnimationState state;
    state.duration = duration;

    // Generate frames for the specified state by creating IntRects for each frame
    for (int i = 0; i < frameCount; ++i) {
        state.frames.emplace_back(
            i * animationSprite[spriteName]->frameSize.x, startRow * animationSprite[spriteName]->frameSize.y, 
            animationSprite[spriteName]->frameSize.x, animationSprite[spriteName]->frameSize.y
        );
    }

    // Add the state to the map of states
    animationSprite[spriteName]->states[stateName] = state;

    // Set the current state if it's the first state being added
    if (animationSprite[spriteName]->currentState == nullptr) {
        animationSprite[spriteName]->currentState = &animationSprite[spriteName]->states[stateName];
    }
}

// Change to a different state
void SpriteAnimation::changeState(const std::string& spriteName, const std::string& stateName, bool resetCurrentFrame) {
    // Find the new state in the map
    auto it = animationSprite[spriteName]->states.find(stateName);
    if (it != animationSprite[spriteName]->states.end()) {
        // Save the current frame from the current state
        int currentFrame = animationSprite[spriteName]->currentState->currentFrame;
        // Update the current state to the new state
        animationSprite[spriteName]->currentState = &it->second;
        // Retain the current frame if not resetting
        animationSprite[spriteName]->currentState->currentFrame = currentFrame;
        // Reset the current frame to the first frame if specified
        if (resetCurrentFrame) {
            animationSprite[spriteName]->currentState->currentFrame = 0;
        }
    } else {
        // Throw an error if the state is not found
        throw std::runtime_error("State not found: " + stateName);
    }
}

// Move the sprite by a given offset
void SpriteAnimation::moveSprite(const std::string& spriteName, sf::Vector2f offset) {
    animationSprite[spriteName]->sprite.move(offset);

#ifdef _DEBUG
    // Update debug shape position when moving the sprite
    debugShape[spriteName].move(offset);
#endif
}

// Update the animation frame based on elapsed time
void SpriteAnimation::updateAnimation(const std::string& spriteName, float deltaTime) {
    if (animationSprite[spriteName]->currentState) {
        // Update elapsed time for the current animation state
        animationSprite[spriteName]->currentState->elapsedTime += deltaTime;

        // Check if it's time to switch to the next frame
        if (animationSprite[spriteName]->currentState->elapsedTime >= animationSprite[spriteName]->currentState->duration) {
            // Reset elapsed time
            animationSprite[spriteName]->currentState->elapsedTime -= animationSprite[spriteName]->currentState->duration;

            // Move to the next frame, looping back to the first frame if necessary
            animationSprite[spriteName]->currentState->currentFrame = (animationSprite[spriteName]->currentState->currentFrame + 1) % animationSprite[spriteName]->currentState->frames.size();
        }

        // Set the current frame texture rectangle for the sprite
        animationSprite[spriteName]->sprite.setTextureRect(animationSprite[spriteName]->currentState->frames[animationSprite[spriteName]->currentState->currentFrame]);
    }
}

// Draw the current frame of the animation
void SpriteAnimation::drawAnimation(const std::string& spriteName) {
    windowInstance->draw(animationSprite[spriteName]->sprite);

#ifdef _DEBUG
    // Optionally draw the debug shape to visualize the sprite bounds
    windowInstance->draw(debugShape[spriteName]);
#endif
}
