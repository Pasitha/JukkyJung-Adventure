#include "SpriteAnimation.h"

// Constructor
SpriteAnimation::SpriteAnimation() : currentFrame(0), duration(0), elapsedTime(0) {}

// Load animation frames from a sprite sheet
void SpriteAnimation::Load(const std::string& filePath, sf::Vector2i frameSize, int frameCount, float duration) {
    this->duration = duration;

    // Load the texture from file
    FileManager::LoadFromFile(texture, filePath);
 
    sprite.setTexture(texture);

    // Generate frames
    for (int i = 0; i < frameCount; i++) {
        frames.emplace_back(i * frameSize.x, 0, frameSize.x, frameSize.y);
    }
}

// Update the animation frame based on elapsed time
void SpriteAnimation::Update(float deltaTime) {
    elapsedTime += deltaTime;
    if (elapsedTime >= duration) {
        elapsedTime = 0;
        currentFrame = (currentFrame + 1) % frames.size();
        sprite.setTextureRect(frames[currentFrame]);
    }
}

// Draw the current frame
void SpriteAnimation::Draw(sf::RenderWindow& window, sf::Vector2f position) {
    sprite.setPosition(position);
    window.draw(sprite);
}
