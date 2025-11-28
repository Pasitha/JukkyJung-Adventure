#pragma once
#include "Scene.h"
#include "UIElementManager.h"
#include "SpriteAnimation.h"

class MainMenuScene : public Scene {
public:
    MainMenuScene(sf::RenderWindow* window);
    ~MainMenuScene();

    void handleEvents(sf::Event& event) override;
    void update(sf::Time deltaTime) override;
    void render(Renderer& renderer) override;

private:
    std::unique_ptr<UIElementManager> uiElement;
    std::unique_ptr<SpriteAnimation> spriteAnimation;
};
