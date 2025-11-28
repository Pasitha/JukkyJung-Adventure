#include "PauseMenuScene.h"
#include "Game.h"
#include "Button.h"
#include "Renderer.h"

PauseMenuScene::PauseMenuScene(sf::RenderWindow* window) {
    uiElement = std::make_unique<UIElementManager>(window);

    auto resumeButton = std::make_unique<Button>("RESUME", Game::getInstance()->getFont(), sf::Vector2f(850, 300), [](){
        Game::getInstance()->changeScene(Scene::GamePlay);
    });
    uiElement->addElement(std::move(resumeButton));

    auto exitButton = std::make_unique<Button>("EXIT", Game::getInstance()->getFont(), sf::Vector2f(850, 500), [](){
        Game::getInstance()->changeScene(Scene::MainMenu);
    });
    uiElement->addElement(std::move(exitButton));

    background.setSize({ 1920.f, 1080.f });
    background.setFillColor(sf::Color(0, 0, 0, 155));

    pauseText.setString("Pause");
    pauseText.setFont(Game::getInstance()->getFont());
    pauseText.setPosition({ 960, 100 });
}

PauseMenuScene::~PauseMenuScene() {}

void PauseMenuScene::handleEvents(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        Game::getInstance()->changeScene(Scene::GamePlay);
    }
    uiElement->handleEvents(event);
}

void PauseMenuScene::update(sf::Time deltaTime) {
    uiElement->update(deltaTime);
}

void PauseMenuScene::render(Renderer& renderer) {
    Game::getInstance()->getScene(Scene::GamePlay)->render(renderer);
    renderer.draw(background);
    renderer.draw(pauseText);
    uiElement->draw();
}
