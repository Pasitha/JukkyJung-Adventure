#include "Game.h"
#include "MainMenuScene.h"
#include "GamePlayScene.h"
#include "SettingScene.h"
#include "PauseMenuScene.h"
#include "AssetManager.h"

Game* Game::instance = nullptr;

Game::Game() : window(sf::VideoMode(1920, 1080), "JukkyJung Adventure", sf::Style::Fullscreen), renderer(window) {
    instance = this;
    window.setFramerateLimit(60);
    gameFont = *AssetManager<sf::Font>::getInstance().get("asset/UI/Font/kenvector_future.ttf");

    scenes[Scene::MainMenu] = std::make_unique<MainMenuScene>(&window);
    scenes[Scene::GamePlay] = std::make_unique<GamePlayScene>(&window);
    scenes[Scene::Setting] = std::make_unique<SettingScene>(&window);
    scenes[Scene::PauseMenu] = std::make_unique<PauseMenuScene>(&window);

    currentScene = scenes[Scene::MainMenu].get();
}

Game::~Game() {}

Game* Game::getInstance() {
    return instance;
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        handleEvents();
        update(deltaTime);
        render();
    }
}

void Game::changeScene(Scene::Type sceneType) {
    currentScene = scenes[sceneType].get();
}

Scene* Game::getScene(Scene::Type sceneType) {
    return scenes[sceneType].get();
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        currentScene->handleEvents(event);
    }
}

void Game::update(sf::Time deltaTime) {
    currentScene->update(deltaTime);
}

void Game::render() {
    renderer.clear();
    currentScene->render(renderer);
    renderer.display();
}
