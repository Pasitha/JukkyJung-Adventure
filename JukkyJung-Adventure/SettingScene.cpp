#include "SettingScene.h"
#include "Game.h"
#include "Button.h"
#include "Slider.h"
#include "Renderer.h"

SettingScene::SettingScene(sf::RenderWindow* window) {
    uiElement = std::make_unique<UIElementManager>(window);

    auto backButton = std::make_unique<Button>("BACK", Game::getInstance()->getFont(), sf::Vector2f(50, 500), [this](){
        Game::getInstance()->changeScene(Scene::MainMenu);
    });
    uiElement->addElement(std::move(backButton));

    auto masterVolumeSlider = std::make_unique<Slider>(Game::getInstance()->getFont(), sf::Vector2f(600, 350), "MASTER VOLUME", 0, 100, [](float value){});
    uiElement->addElement(std::move(masterVolumeSlider));

    auto musicSlider = std::make_unique<Slider>(Game::getInstance()->getFont(), sf::Vector2f(600, 450), "MUSIC", 0, 100, [](float value){});
    uiElement->addElement(std::move(musicSlider));

    auto fxSlider = std::make_unique<Slider>(Game::getInstance()->getFont(), sf::Vector2f(600, 550), "FX", 0, 100, [](float value){});
    uiElement->addElement(std::move(fxSlider));
}

SettingScene::~SettingScene() {}

void SettingScene::handleEvents(sf::Event& event) {
    uiElement->handleEvents(event);
}

void SettingScene::update(sf::Time deltaTime) {
    uiElement->update(deltaTime);
}

void SettingScene::render(Renderer& renderer) {
    uiElement->draw();
}
