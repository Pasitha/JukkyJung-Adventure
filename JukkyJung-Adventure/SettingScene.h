#pragma once
#include "Scene.h"
#include "UIElementManager.h"

class SettingScene : public Scene {
public:
    SettingScene(sf::RenderWindow* window);
    ~SettingScene();

    void handleEvents(sf::Event& event) override;
    void update(sf::Time deltaTime) override;
    void render(Renderer& renderer) override;

private:
    std::unique_ptr<UIElementManager> uiElement;
};
