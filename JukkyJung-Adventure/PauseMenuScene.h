#pragma once
#include "Scene.h"
#include "UIElementManager.h"

class PauseMenuScene : public Scene {
public:
    PauseMenuScene(sf::RenderWindow* window);
    ~PauseMenuScene();

    void handleEvents(sf::Event& event) override;
    void update(sf::Time deltaTime) override;
    void render(Renderer& renderer) override;

private:
    std::unique_ptr<UIElementManager> uiElement;
    sf::RectangleShape background;
    sf::Text pauseText;
};
