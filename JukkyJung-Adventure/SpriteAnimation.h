#pragma once
#include "common.h"

class SpriteAnimation {
public:
    SpriteAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);

    void Update(int row, float deltaTime);

    sf::IntRect uvRect;
private:
    // Pointer to the SFML render window
    // sf::RenderWindow* windowInstance;

    sf::Vector2u imageCount;
    sf::Vector2u currentImage;

    float totalTime;
    float switchTime;
};

