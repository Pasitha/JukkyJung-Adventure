#include "MainMenuScene.h"
#include "Game.h"
#include "Button.h"
#include "Renderer.h"

MainMenuScene::MainMenuScene(sf::RenderWindow* window) {
    uiElement = std::make_unique<UIElementManager>(window);

    auto playButton = std::make_unique<Button>("Play", Game::getInstance()->getFont(), sf::Vector2f(150, 300), []() {
        Game::getInstance()->changeScene(Scene::GamePlay);
    });
    uiElement->addElement(std::move(playButton));

    auto settingButton = std::make_unique<Button>("Setting", Game::getInstance()->getFont(), sf::Vector2f(150, 500), []() {
        Game::getInstance()->changeScene(Scene::Setting);
    });
    uiElement->addElement(std::move(settingButton));

    auto exitButton = std::make_unique<Button>("Exit", Game::getInstance()->getFont(), sf::Vector2f(150, 700), []() {
        Game::getInstance()->getWindow().close();
    });
    uiElement->addElement(std::move(exitButton));

    spriteAnimation = std::make_unique<SpriteAnimation>(window);
    spriteAnimation->loadSpriteSheet("asset/Planet-Sprite.png", "planet", {256, 256}, 1, {1000, 220});
    spriteAnimation->setScale("planet", { 2.5f, 2.5f });
    spriteAnimation->setState("planet", "Idel", 0, 50, .10f);
    spriteAnimation->changeState("planet", "Idel");
}

MainMenuScene::~MainMenuScene() {}

void MainMenuScene::handleEvents(sf::Event& event) {
    uiElement->handleEvents(event);
}

void MainMenuScene::update(sf::Time deltaTime) {
    uiElement->update(deltaTime);
    spriteAnimation->updateAnimation("planet", deltaTime.asSeconds());
}

void MainMenuScene::render(Renderer& renderer) {
    spriteAnimation->drawAnimation("planet");
    uiElement->draw();
}
