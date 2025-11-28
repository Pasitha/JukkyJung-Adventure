#pragma once
#include "Scene.h"
#include "UIElementManager.h"
#include "SpriteAnimation.h"
#include "MapManager.h"

class Combat; // Forward declaration

class GamePlayScene : public Scene {
public:
    GamePlayScene(sf::RenderWindow* window);
    ~GamePlayScene();

    void handleEvents(sf::Event& event) override;
    void update(sf::Time deltaTime) override;
    void render(Renderer& renderer) override;

private:
    void handlePlayerMovement(sf::Time deltaTime);

    std::unique_ptr<UIElementManager> uiElement;
    std::unique_ptr<SpriteAnimation> spriteAnimation;
    std::unique_ptr<MapManager> map;
    std::unique_ptr<Combat> combat;
    bool isInCombat;
};
