#include "common.h"

// Constructor to initialize the game
Game::Game() :
    window(sf::VideoMode(1920, 1080), "JukkyJuung Adventure", sf::Style::Fullscreen),
    currentScene(Scene::MainMenu),
    isGamePaused(false)
{
    // Set a frame rate limit to the window
    window.setFramerateLimit(60);

    // Load the game font from a file
    FileManager::LoadFromFile(gameFont, "asset/font/ReadexPro.ttf");

    // Initialize variables related to the game pause menu
    backgroundPauseMenuText.setString("Pause");
    backgroundPauseMenuText.setFont(gameFont);
    backgroundPauseMenuText.setPosition({ 960, 100 });

    backgroundPauseMenu.setSize({ 1920.f, 1080.f });
    backgroundPauseMenu.setFillColor(sf::Color(0, 0, 0, 155));

    // Initialize game components for each scene
    sceneComponents[Scene::MainMenu] = std::make_unique<SceneComponents>();
    sceneComponents[Scene::GamePlay] = std::make_unique<SceneComponents>();
    sceneComponents[Scene::PauseMenu] = std::make_unique<SceneComponents>();

    // Create and associate buttons with each scene
    sceneComponents[Scene::MainMenu]->button = std::make_unique<Button>(&window);
    sceneComponents[Scene::GamePlay]->button = std::make_unique<Button>(&window);
    sceneComponents[Scene::GamePlay]->character = std::make_unique<Character>();
    sceneComponents[Scene::PauseMenu]->button = std::make_unique<Button>(&window);

    sceneComponents[Scene::GamePlay]->character->addCharacter("JukkyJung", 120, 10, ElementalPower::Time, "asset/picture/JukkyJung.png");

    // Initialize scene components with buttons and their positions
    InitializeSceneComponents(Scene::MainMenu, { {"Play", {50, 300}}, {"Setting", {50, 500}}, {"Exit", {50, 700}} });
    InitializeSceneComponents(Scene::GamePlay, { {"ATTACK", {50, 800}}, {"ITEM", {400, 800}}, {"SKIP ROUND", {750, 800}} });
    InitializeSceneComponents(Scene::PauseMenu, { {"RESUME", {850, 300}}, {"EXIT", {850, 500}} });
}

#ifdef _DEBUG
// Destructor implementation only in debug mode as a reminder for cleanup
Game::~Game() {
    std::cout << "Game was destroyed!" << std::endl;
}
#endif

// Initialize scene components with buttons and their positions
void Game::InitializeSceneComponents(Scene scene, const std::vector<std::pair<std::string, sf::Vector2f>>& buttons) {
    auto& sceneComp = *sceneComponents[scene];

    sceneComp.button = std::make_unique<Button>(&window);

    // Add buttons to the scene component
    for (const auto& button : buttons) {
        sceneComp.button->addButton(button.first, button.second);
    }
}

// Handle events based on the current game scene
void Game::HandleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // The event check handles each game scene separately.
        switch (currentScene) {
        case Scene::MainMenu:
            // Handle events for the main menu scene
            if (event.type == sf::Event::MouseMoved) {
                sceneComponents[Scene::MainMenu]->button->isHover();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                switch (sceneComponents[Scene::MainMenu]->button->whichButtonHover()) {
                case 0:
                    currentScene = Scene::GamePlay;
                    break;
                case 1:
                    currentScene = Scene::Setting;
                    break;
                case 2:
                    window.close();
                    break;
                }
            }
            break;
        case Scene::GamePlay:
            // Handle events for the game play scene
            if (event.type == sf::Event::MouseMoved) {
                sceneComponents[Scene::GamePlay]->button->isHover();
                if (isGamePaused) {
                    sceneComponents[Scene::PauseMenu]->button->isHover();
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                switch (sceneComponents[Scene::GamePlay]->button->whichButtonHover()) {
                case 0:
                    // sceneComponents[Scene::GamePlay]->character->ShakeAnimation();
                    break;
                case 1:
                    // Handle ITEM button press
                    break;
                case 2:
                    // Handle SKIP ROUND button press
                    break;
                }

                if (isGamePaused) {
                    switch (sceneComponents[Scene::PauseMenu]->button->whichButtonHover()) {
                    case 0:
                        isGamePaused = false;
                        break;
                    case 1:
                        currentScene = Scene::MainMenu;
                        break;
                    }
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape && !isGamePaused) {
                    isGamePaused = true;
                }
                else if (event.key.code == sf::Keyboard::Escape && isGamePaused) {
                    isGamePaused = false;
                }
            }
            break;
        }
    }
}

// Render the current game scene
void Game::Render() {
    window.clear(sf::Color(199, 119, 19, 255));

    switch (currentScene) {
    case Scene::MainMenu:
        // Render the main menu scene
        sceneComponents[Scene::MainMenu]->button->update();
        break;
    case Scene::Setting:
        // Render the settings scene (not yet implemented)
        break;
    case Scene::GamePlay:
        // Render the game play scene
        sceneComponents[Scene::GamePlay]->button->update();
        sceneComponents[Scene::GamePlay]->character->draw(&window, "JukkyJung");
        // sceneComponents[Scene::GamePlay]->jukkyJung->Update();
        // sceneComponents[Scene::GamePlay]->enemy->Update();

        if (isGamePaused) {
            // Render the pause menu when the game is paused
            window.draw(backgroundPauseMenu);
            window.draw(backgroundPauseMenuText);

            sceneComponents[Scene::PauseMenu]->button->update();
        }
        break;
    }
    window.display();
}

// Run the game loop
void Game::GameLoop() {
    while (window.isOpen()) {
        HandleEvents();
        Render();
    }
}
