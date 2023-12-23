#include "common.h"

// Constructor to initialize the game
Game::Game() :
    m_window(sf::VideoMode(1920, 1080), "JukkyJuung Adventure", sf::Style::Fullscreen), 
    m_gameScene(Scene::mainMenu),
    m_isGamePause(false)
{
    // Set a frame rate limit to the window
    this->m_window.setFramerateLimit(60);

    // Load the game font from a file
    FileManager::LoadFromFile(this->m_gameFont, "asset/font/ReadexPro.ttf");

    // Initialize variables related to the game pause menu
    this->m_backgroundPauseMenuText.setString("Pause");
    this->m_backgroundPauseMenuText.setFont(this->m_gameFont);
    this->m_backgroundPauseMenuText.setPosition({ 960, 100 });
    this->m_backgroundPauseMenu.setSize({ 1920.f, 1080.f });
    this->m_backgroundPauseMenu.setFillColor(sf::Color(0, 0, 0, 155));

    // Initialize game components for each scene
    this->m_SceneComponent[Scene::mainMenu] = std::make_unique<m_gameComponent>(); 
    this->m_SceneComponent[Scene::gamePlay] = std::make_unique<m_gameComponent>(); 
    this->m_SceneComponent[Scene::pauseMenu] = std::make_unique<m_gameComponent>();

    // Create and associate buttons with each scene
    this->m_SceneComponent[Scene::mainMenu]->m_Button = std::make_unique<Button>(&this->m_window);
    this->m_SceneComponent[Scene::gamePlay]->m_Button = std::make_unique<Button>(&this->m_window);
    this->m_SceneComponent[Scene::gamePlay]->m_JukkyJung = std::make_unique<JukkyJung>(&this->m_window);
    this->m_SceneComponent[Scene::gamePlay]->m_Enemy = std::make_unique<Enemy>(&this->m_window);
    this->m_SceneComponent[Scene::gamePlay]->m_Character = std::make_unique<Character>();
    this->m_SceneComponent[Scene::pauseMenu]->m_Button = std::make_unique<Button>(&this->m_window);
    
    // Initialize scene components with buttons and their positions
    initializeSceneComponent(Scene::mainMenu, { {"Play", {50, 300}}, {"Setting", {50, 500}}, {"Exit", {50, 700}} });
    initializeSceneComponent(Scene::gamePlay, { {"ATTACK", {50, 800}}, {"ITEM", {400, 800}}, {"SKIP ROUND", {750, 800}} });
    initializeSceneComponent(Scene::pauseMenu, { {"RESUME", {850, 300}}, {"EXIT", {850, 500}} });

}

// Destructor implementation only in debug mode
#ifdef _DEBUG
Game::~Game() {
    std::cout << "Game was destory!" << std::endl;
}
#endif

// Initialize scene components with buttons and their positions
void Game::initializeSceneComponent(Scene scene, const std::vector<std::pair<std::string, sf::Vector2f>>& buttons) {
    auto& sceneComp = *this->m_SceneComponent[scene];

    sceneComp.m_Button = std::make_unique<Button>(&this->m_window);

    // Add buttons to the scene component
    for (const auto& button : buttons) {
        sceneComp.m_Button->addButton(button.first, button.second);
    }
}

// Handle events based on the current game scene
void Game::HandleEvents() {
    sf::Event event;
    while (this->m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->m_window.close();
        }

        // The event check handles each game scene separately.
        switch (m_gameScene) {
        case Scene::mainMenu:
            // Handle events for the main menu scene
            if (event.type == sf::Event::MouseMoved) {
                this->m_SceneComponent[Scene::mainMenu]->m_Button->isHover();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                switch (this->m_SceneComponent[Scene::mainMenu]->m_Button->whichButtonHover()) {
                case 0:
                    this->m_gameScene = Scene::gamePlay;
                    break;
                case 1:
                    this->m_gameScene = Scene::setting;
                    break;
                case 2:
                    this->m_window.close();
                    break;
                }
            }
            break;
        case Scene::gamePlay:
            // Handle events for the game play scene
            if (event.type == sf::Event::MouseMoved) {
                this->m_SceneComponent[Scene::gamePlay]->m_Button->isHover();
                if (this->m_isGamePause) {
                    this->m_SceneComponent[Scene::pauseMenu]->m_Button->isHover();
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                switch (this->m_SceneComponent[Scene::gamePlay]->m_Button->whichButtonHover()) {
                case 0:
                    this->m_SceneComponent[Scene::gamePlay]->m_JukkyJung->ShakeAnimation();
                    break;
                case 1:
                    break;
                case 2:
                    break;
                }

                if (this->m_isGamePause) {
                    switch (this->m_SceneComponent[Scene::pauseMenu]->m_Button->whichButtonHover()) {
                    case 0:
                        this->m_isGamePause = false;
                        break;
                    case 1:
                        this->m_gameScene = Scene::mainMenu;
                        break;
                    }
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape && !this->m_isGamePause) {
                    this->m_isGamePause = true;
                }
                else if (event.key.code == sf::Keyboard::Escape && this->m_isGamePause) {
                    this->m_isGamePause = false;
                }
            }
            break;
        }
    }
}

// Render the current game scene
void Game::Render() {
    this->m_window.clear(sf::Color(199, 119, 19, 255));
    switch (m_gameScene) {
        case Scene::mainMenu:
            // Render the main menu scene
            this->m_SceneComponent[Scene::mainMenu]->m_Button->Update();
            break;
        case Scene::setting:
            // Render the settings scene
            break;
        case Scene::gamePlay:
            // Render the game play scene
            this->m_SceneComponent[Scene::gamePlay]->m_Button->Update();
            this->m_SceneComponent[Scene::gamePlay]->m_JukkyJung->Update();
            this->m_SceneComponent[Scene::gamePlay]->m_Enemy->Update();

            if (this->m_isGamePause) {
                // Render the pause menu when the game is paused
                this->m_window.draw(m_backgroundPauseMenu);
                this->m_window.draw(m_backgroundPauseMenuText);

                this->m_SceneComponent[Scene::pauseMenu]->m_Button->Update();
            }
            break;
    }
    this->m_window.display();
}

// Run the game loop
void Game::GameLoop() {
    while (this->m_window.isOpen()) {
        HandleEvents();
        Render();
    }
}
