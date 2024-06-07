#include "common.h"

// Constructor to initialize the game
Game::Game() :
    window(sf::VideoMode(1920, 1080), "JukkyJuung Adventure", sf::Style::Fullscreen),
    currentScene(Scene::MainMenu),
    isGamePaused(false),
    isEscapePressed(false)
{
    // Set a frame rate limit to the window
    window.setFramerateLimit(60);

    // Load the game font from a file
    FileManager::LoadFromFile(gameFont, "asset/UI/Font/kenvector_future.ttf");

    // Initialize variables related to the game pause menu
    backgroundPauseMenuText.setString("Pause");
    backgroundPauseMenuText.setFont(gameFont);
    backgroundPauseMenuText.setPosition({ 960, 100 });

    backgroundPauseMenu.setSize({ 1920.f, 1080.f });
    backgroundPauseMenu.setFillColor(sf::Color(0, 0, 0, 155));

    // Initialize game components for each scene
    sceneComponents[Scene::MainMenu] = std::make_unique<SceneComponents>();
    sceneComponents[Scene::GamePlay] = std::make_unique<SceneComponents>();
    sceneComponents[Scene::Setting] = std::make_unique<SceneComponents>();
    sceneComponents[Scene::PauseMenu] = std::make_unique<SceneComponents>();

    // Create and associate buttons with each scene
    sceneComponents[Scene::MainMenu]->uiElement = std::make_unique<UIElementManager>(&window);
    sceneComponents[Scene::Setting]->uiElement = std::make_unique<UIElementManager>(&window);
    sceneComponents[Scene::GamePlay]->uiElement = std::make_unique<UIElementManager>(&window);
    sceneComponents[Scene::PauseMenu]->uiElement = std::make_unique<UIElementManager>(&window);
    
    // Initialize asset manager for each scene
    sceneComponents[Scene::MainMenu]->spriteAnimation = std::make_unique<SpriteAnimation>(&window);
    sceneComponents[Scene::GamePlay]->spriteAnimation = std::make_unique<SpriteAnimation>(&window);

    sceneComponents[Scene::MainMenu]->spriteAnimation->loadSpriteSheet("asset/Planet-Sprite.png", { 256, 256 }, 1, {1000, 220});
    sceneComponents[Scene::MainMenu]->spriteAnimation->setScale({ 2.5f, 2.5f });
    sceneComponents[Scene::MainMenu]->spriteAnimation->setState("Idel", 0, 50, .10f);
    sceneComponents[Scene::MainMenu]->spriteAnimation->changeState("Idel");

    sceneComponents[Scene::GamePlay]->spriteAnimation->loadSpriteSheet("asset/JukkyJung-Sprite.png", { 64, 64 }, 24, {1000, 220});
    sceneComponents[Scene::GamePlay]->spriteAnimation->setScale({ 2.5f, 2.5f });
    sceneComponents[Scene::GamePlay]->spriteAnimation->setState("Idel-back", 0, 7, .35f);
    sceneComponents[Scene::GamePlay]->spriteAnimation->setState("Idel-left", 1, 7, .35f);
    sceneComponents[Scene::GamePlay]->spriteAnimation->setState("Idel-front", 2, 7, .35f);
    sceneComponents[Scene::GamePlay]->spriteAnimation->setState("Idel-right", 3, 7, .35f);
    sceneComponents[Scene::GamePlay]->spriteAnimation->changeState("Idel-front");

    // Initialize scene components with buttons and their positions
    sceneComponents[Scene::MainMenu]->uiElement->addButton({ {"Play", {150, 300}}, {"Setting", {150, 500}}, {"Exit", {150, 700}} }, TextAlignment::Center);
    sceneComponents[Scene::Setting]->uiElement->addButton({ {"VOLUME", {50, 300}}, {"BACK", {50, 500}} }, TextAlignment::Center);
    sceneComponents[Scene::GamePlay]->uiElement->addButton({ {"ATTACK", {50, 800}}, {"ITEM", {400, 800}}, {"SKIP ROUND", {750, 800}} }, TextAlignment::Center);
    sceneComponents[Scene::PauseMenu]->uiElement->addButton({ {"RESUME", {850, 300}}, {"EXIT", {850, 500}} }, TextAlignment::Center);

    sceneComponents[Scene::Setting]->uiElement->addSlider("MASTER VOLUME", { 600, 350 });
    sceneComponents[Scene::Setting]->uiElement->addSlider("MUSIC", { 600, 450 });
    sceneComponents[Scene::Setting]->uiElement->addSlider("FX", { 600, 550 });
}

#ifdef _DEBUG
// Destructor implementation only in debug mode as a reminder for cleanup
Game::~Game() {
    std::cout << "Game was destroyed!" << std::endl;
}
#endif

void Game::handleHover(Scene currentScene, bool isGamePaused) {
	sceneComponents[currentScene]->uiElement->updateHover();
}

void Game::handleButtonPress(int buttonHoverId) {
    switch (currentScene) {
    case Scene::MainMenu:
        switch (buttonHoverId) {
        case 0:
            sceneComponents[Scene::MainMenu]->uiElement->setColor(buttonHoverId, ElementState::Pressed);
            currentScene = Scene::GamePlay;
            sceneComponents[Scene::MainMenu]->uiElement->setColor(buttonHoverId, ElementState::Normal);
#ifdef _DEBUG
            std::cout << "Change to Gameplay scene" << std::endl;
#endif
            break;
        case 1:
            sceneComponents[Scene::MainMenu]->uiElement->setColor(buttonHoverId, ElementState::Pressed);
            currentScene = Scene::Setting;
            sceneComponents[Scene::MainMenu]->uiElement->setColor(buttonHoverId, ElementState::Normal);
            break;
        case 2:
            window.close();
            break;
        }
        break;
    case Scene::Setting:
        switch (buttonHoverId) {
        case 0:
            sceneComponents[Scene::Setting]->uiElement->setColor(buttonHoverId, ElementState::Pressed);
            break;
        case 1:
            sceneComponents[Scene::Setting]->uiElement->setColor(buttonHoverId, ElementState::Pressed);
            currentScene = Scene::MainMenu;
            sceneComponents[Scene::Setting]->uiElement->setColor(buttonHoverId, ElementState::Normal);
            break;
        case 2: case 3: case 4:
            sceneComponents[Scene::Setting]->uiElement->setThumbPosition(buttonHoverId);
            break;
        }
        break;
    case Scene::GamePlay:
        switch (buttonHoverId) {
        case 0:
            sceneComponents[Scene::GamePlay]->uiElement->setColor(buttonHoverId, ElementState::Normal);
            break;
        case 1:
            sceneComponents[Scene::GamePlay]->uiElement->setColor(buttonHoverId, ElementState::Normal);
            break;
        case 2:
            sceneComponents[Scene::GamePlay]->uiElement->setColor(buttonHoverId, ElementState::Normal);
            break;
        }
        break;
    case Scene::PauseMenu:
        switch (buttonHoverId) {
        case 0:
            sceneComponents[Scene::PauseMenu]->uiElement->setColor(buttonHoverId, ElementState::Pressed);
            isGamePaused = false;
            sceneComponents[Scene::PauseMenu]->uiElement->setColor(buttonHoverId, ElementState::Normal);
            currentScene = Scene::GamePlay;
            break;
        case 1:
            sceneComponents[Scene::PauseMenu]->uiElement->setColor(buttonHoverId, ElementState::Pressed);
            isGamePaused = false;
            sceneComponents[Scene::PauseMenu]->uiElement->setColor(buttonHoverId, ElementState::Normal);
            currentScene = Scene::MainMenu;
            break;
        }
        break;
    }
}

// Handle events based on the current game scene
void Game::HandleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // Handle hover events
        if (event.type == sf::Event::MouseMoved) {
            handleHover(currentScene, isGamePaused);
        }

        // Handle button press events
        if (event.type == sf::Event::MouseButtonPressed) {
            int buttonHoverId = sceneComponents[currentScene]->uiElement->whichElementHover();
            handleButtonPress(buttonHoverId);
        }

        // Handle Escape key press for pausing and resuming
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape && !isEscapePressed && currentScene == Scene::GamePlay) {
#ifdef _DEBUG
				std::cout << "Escape key in Scene" << (int)currentScene << std::endl;
#endif

                isEscapePressed = true;
                if (!isGamePaused) {
					currentScene = Scene::PauseMenu;
                    isGamePaused = true;
                }
                else {
					currentScene = Scene::GamePlay;
                    isGamePaused = false;
                }
            }
        }

        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Escape) {
                isEscapePressed = false;
            }
        }

        if (currentScene == Scene::GamePlay) {
            sf::Vector2f movement(0.f, 0.f);
            std::string state;

            // Process movement keys
            const std::map<sf::Keyboard::Key, std::pair<std::string, sf::Vector2f>> movementMap = {
				{sf::Keyboard::W, {"Idel-back", {0.f, -2.f}}},
				{sf::Keyboard::A, {"Idel-left", {-2.f, 0.f}}},
				{sf::Keyboard::S, {"Idel-front", {0.f, 2.f}}},
				{sf::Keyboard::D, {"Idel-right", {2.f, 0.f}}},
            };
            /*
				0
				3
				18
				22
            */

            auto it = movementMap.find(event.key.code);
            if (it != movementMap.end()) {
                state = it->second.first;
                movement = it->second.second;
            }

            // Update animation and position if there's movement
            if (movement != sf::Vector2f(0.f, 0.f)) {
                sceneComponents[currentScene]->spriteAnimation->changeState(state);
                sceneComponents[currentScene]->spriteAnimation->moveSprite(movement);
#ifdef _DEBUG
                std::cout << "Change animation state to " << state << std::endl;
                
                for (const auto& [key, pair] : movementMap) {
                    std::cout << key << std::endl;
                }
#endif
            }
        }
    }
}

// Render the current game scene
void Game::Render() {
    window.clear(sf::Color(199, 119, 19, 255));
    
    // Render the button on currentScene
	sceneComponents[currentScene]->uiElement->update();

    if (currentScene == Scene::MainMenu || currentScene == Scene::GamePlay) {
		// Render the spriteAnimation on currentScene
        sceneComponents[currentScene]->spriteAnimation->updateAnimation(deltaTime);
        sceneComponents[currentScene]->spriteAnimation->drawAnimation();
    }

    if (currentScene == Scene::Setting) {
        sceneComponents[Scene::Setting]->uiElement->update();
    }
    
    if (currentScene == Scene::PauseMenu && isGamePaused) {
		// Render the button on currentScene
		sceneComponents[Scene::GamePlay]->uiElement->update();

		// Render the spriteAnimation on currentScene
        sceneComponents[Scene::GamePlay]->spriteAnimation->updateAnimation(deltaTime);
        sceneComponents[Scene::GamePlay]->spriteAnimation->drawAnimation();

		// Render the pause menu when the game is paused
		window.draw(backgroundPauseMenu);
		window.draw(backgroundPauseMenuText);

		sceneComponents[Scene::PauseMenu]->uiElement->update();
    }
	window.display();
}

// Run the game loop
void Game::GameLoop() {
    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();
        HandleEvents();
        Render();
    }
}
