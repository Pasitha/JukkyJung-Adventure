#include "SpriteAnimation.h"

// Constructor implementation
SpriteAnimation::SpriteAnimation(sf::RenderWindow* window)
    : windowInstance(window), textureManager(AssetManager<sf::Texture>::getInstance())
{
    // Constructor body can be empty if initialization is done in the header
}

// Method to load a sprite sheet
void SpriteAnimation::loadSpriteSheet(const std::string& filePath, const std::string& spriteName, sf::Vector2i frameSize, uint64_t rowCount, sf::Vector2f position)
{
    // Create a new AnimationSprite and store it in the map
    auto spriteSheet = std::make_shared<AnimationSprite>();
    spriteSheet->texture = textureManager.get(filePath);
    spriteSheet->sprite.setTexture(*spriteSheet->texture);
    spriteSheet->frameSize = frameSize;
    spriteSheet->rowCount = rowCount;
    spriteSheet->sprite.setPosition(position);
    animationSprites[spriteName] = spriteSheet;
}

// Method to set the scale of a sprite
void SpriteAnimation::setScale(const std::string& spriteName, const sf::Vector2f& scale)
{
    // Set the scale of the specified sprite
    animationSprites[spriteName]->sprite.setScale(scale);
}

// Method to set an animation state with a specified row and frame count
void SpriteAnimation::setState(const std::string& spriteName, const std::string& stateName, uint64_t startRow, uint64_t frameCount, float duration)
{
    // Get the sprite sheet
    auto& spriteSheet = animationSprites[spriteName];
    // Create a new animation state
    AnimationState state;
    state.duration = duration;
    // Calculate the frames for the state
    for (uint64_t i = 0; i < frameCount; ++i) {
        state.frames.push_back(sf::IntRect(i * spriteSheet->frameSize.x, startRow * spriteSheet->frameSize.y, spriteSheet->frameSize.x, spriteSheet->frameSize.y));
    }
    // Store the state in the sprite sheet
    spriteSheet->states[stateName] = state;
}

// Method to set an animation state with a specified row and column range
void SpriteAnimation::setState(const std::string& spriteName, const std::string& stateName, uint64_t startRow, uint64_t startCol, uint64_t endCol, float duration)
{
    // Get the sprite sheet
    auto& spriteSheet = animationSprites[spriteName];
    // Create a new animation state
    AnimationState state;
    state.duration = duration;
    // Calculate the frames for the state
    for (uint64_t i = startCol; i < endCol; ++i) {
        state.frames.push_back(sf::IntRect(i * spriteSheet->frameSize.x, startRow * spriteSheet->frameSize.y, spriteSheet->frameSize.x, spriteSheet->frameSize.y));
    }
    // Store the state in the sprite sheet
    spriteSheet->states[stateName] = state;
}

// Method to change the current animation state
void SpriteAnimation::changeState(const std::string& spriteName, const std::string& stateName, bool resetCurrentFrame)
{
    // Get the sprite sheet and set the current state
    auto& spriteSheet = animationSprites[spriteName];
    spriteSheet->currentState = &spriteSheet->states[stateName];

    // Reset the current frame if specified
    if (resetCurrentFrame) {
        spriteSheet->currentState->currentFrame = 0;
    }
}

// Method to get the position of a sprite
const sf::Vector2f& SpriteAnimation::getPosition(const std::string& spriteName) const
{
    // Return the position of the specified sprite
    return animationSprites.at(spriteName)->getPosition();
}

// Method to move a sprite by a given offset
void SpriteAnimation::moveSprite(const std::string& spriteName, sf::Vector2f offset)
{
    // Move the specified sprite
    animationSprites[spriteName]->sprite.move(offset);
}

// Method to update the animation
void SpriteAnimation::updateAnimation(const std::string& spriteName, float deltaTime)
{
    // Get the sprite sheet and its current state
    auto& spriteSheet = animationSprites[spriteName];
    auto& currentState = spriteSheet->currentState;

    // If there is a current state, update the animation
    if (currentState) {
        currentState->elapsedTime += deltaTime;
        if (currentState->elapsedTime >= currentState->duration) {
            currentState->elapsedTime = 0.0f;
            currentState->currentFrame = (currentState->currentFrame + 1) % currentState->frames.size();
        }
    }
}

// Method to draw the animation
void SpriteAnimation::drawAnimation(const std::string& spriteName)
{
    // Get the sprite sheet and its current state
    auto& spriteSheet = animationSprites[spriteName];
    auto& currentState = spriteSheet->currentState;

    // If there is a current state, draw the current frame
    if (currentState) {
        spriteSheet->sprite.setTextureRect(currentState->frames[currentState->currentFrame]);
        windowInstance->draw(spriteSheet->sprite);
    }
}
