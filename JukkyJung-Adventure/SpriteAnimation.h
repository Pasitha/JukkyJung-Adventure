#pragma once
#include "common.h"

class SpriteAnimation {
public:
    SpriteAnimation();

    // Load animation frames from a sprite sheet
    void Load(const std::string& filePath, sf::Vector2i frameSize, int frameCount, float duration);

    // Update the animation frame based on elapsed time
    void Update(float deltaTime);

    // Draw the current frame
    void Draw(sf::RenderWindow& window, sf::Vector2f position);

private:
    std::vector<sf::IntRect> frames;
    sf::Texture texture;
    sf::Sprite sprite;
    int currentFrame;
    float duration;
    float elapsedTime;
};

