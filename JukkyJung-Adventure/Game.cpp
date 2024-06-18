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
    
    // Initialize UI elements (buttons and sliders) for each scene
    sceneComponents[Scene::MainMenu]->uiElement->addButton({ {"Play", {150, 300}}, {"Setting", {150, 500}}, {"Exit", {150, 700}} }, TextAlignment::Center);
    sceneComponents[Scene::Setting]->uiElement->addButton({ {"VOLUME", {50, 300}}, {"BACK", {50, 500}} }, TextAlignment::Center);
    sceneComponents[Scene::GamePlay]->uiElement->addButton({ {"ATTACK", {50, 800}}, {"ITEM", {400, 800}}, {"SKIP ROUND", {750, 800}} }, TextAlignment::Center);
    sceneComponents[Scene::PauseMenu]->uiElement->addButton({ {"RESUME", {850, 300}}, {"EXIT", {850, 500}} }, TextAlignment::Center);

    sceneComponents[Scene::Setting]->uiElement->addSlider("MASTER VOLUME", { 600, 350 });
    sceneComponents[Scene::Setting]->uiElement->addSlider("MUSIC", { 600, 450 });
    sceneComponents[Scene::Setting]->uiElement->addSlider("FX", { 600, 550 });

    // Initialize asset manager for each scene
    sceneComponents[Scene::MainMenu]->spriteAnimation = std::make_unique<SpriteAnimation>(&window);
    sceneComponents[Scene::GamePlay]->spriteAnimation = std::make_unique<SpriteAnimation>(&window);

    // Load and configure sprite animations for the MainMenu scene
    sceneComponents[Scene::MainMenu]->spriteAnimation->loadSpriteSheet("asset/Planet-Sprite.png", "planet", {256, 256}, 1, {1000, 220});
    sceneComponents[Scene::MainMenu]->spriteAnimation->setScale("planet", { 2.5f, 2.5f });
    sceneComponents[Scene::MainMenu]->spriteAnimation->setState("planet", "Idel", 0, 50, .10f);
    sceneComponents[Scene::MainMenu]->spriteAnimation->changeState("planet", "Idel");

    // Load and configure sprite animations for the GamePlay scene
    sceneComponents[Scene::GamePlay]->spriteAnimation->loadSpriteSheet("asset/JukkyJung-Sprite.png", "JukkyJung", { 64, 64 }, 24, {1000, 220});
    sceneComponents[Scene::GamePlay]->spriteAnimation->setScale("JukkyJung", { 2.f, 2.f });
    sceneComponents[Scene::GamePlay]->spriteAnimation->setState("JukkyJung", "Spellcast-back", 0, 7, .35f);
    sceneComponents[Scene::GamePlay]->spriteAnimation->setState("JukkyJung", "Spellcast-left", 1, 7, .35f);
    sceneComponents[Scene::GamePlay]->spriteAnimation->setState("JukkyJung", "Spellcast-front", 2, 7, .35f);
    sceneComponents[Scene::GamePlay]->spriteAnimation->setState("JukkyJung", "Spellcast-right", 3, 7, .35f);
    sceneComponents[Scene::GamePlay]->spriteAnimation->setState("JukkyJung", "Walk-back", 8, 1, 8, .15f);
    sceneComponents[Scene::GamePlay]->spriteAnimation->setState("JukkyJung", "Walk-left", 9, 1, 8, .15f);
    sceneComponents[Scene::GamePlay]->spriteAnimation->setState("JukkyJung", "Walk-front", 10, 1, 8, .15f);
    sceneComponents[Scene::GamePlay]->spriteAnimation->setState("JukkyJung", "Walk-right", 11, 1, 8, .15f);
    sceneComponents[Scene::GamePlay]->spriteAnimation->changeState("JukkyJung", "Spellcast-front");

    sceneComponents[Scene::GamePlay]->spriteAnimation->loadSpriteSheet("asset/Zombie-Sprite.png", "Dummy1", { 64, 64 }, 36, {1500, 220});
    sceneComponents[Scene::GamePlay]->spriteAnimation->setScale("Dummy1", { 2.f, 2.f });
    sceneComponents[Scene::GamePlay]->spriteAnimation->setState("Dummy1", "Walk-left", 9, 8, .35f);
    sceneComponents[Scene::GamePlay]->spriteAnimation->changeState("Dummy1", "Walk-left");

    sceneComponents[Scene::GamePlay]->spriteAnimation->loadSpriteSheet("asset/Zombie-Sprite.png", "Dummy2", { 64, 64 }, 36, {200, 480});
    sceneComponents[Scene::GamePlay]->spriteAnimation->setScale("Dummy2", { 2.f, 2.f });
    sceneComponents[Scene::GamePlay]->spriteAnimation->setState("Dummy2", "Walk-right", 11, 8, .35f);
    sceneComponents[Scene::GamePlay]->spriteAnimation->changeState("Dummy2", "Walk-right");

    sceneComponents[Scene::GamePlay]->spriteAnimation->loadSpriteSheet("asset/Headman-Sprite.png", "Headman", { 64, 64 }, 36, {960, 730});
    sceneComponents[Scene::GamePlay]->spriteAnimation->setScale("Headman", { 2.f, 2.f });
    sceneComponents[Scene::GamePlay]->spriteAnimation->setState("Headman", "Idel-right", 15, 1, 2, .75f);
    sceneComponents[Scene::GamePlay]->spriteAnimation->changeState("Headman", "Idel-right");

    sceneComponents[Scene::GamePlay]->map = std::make_unique<MapManager>(&window);

    sceneComponents[Scene::GamePlay]->map->addMap("village", 32, 32, 32, 32, 60, 34, "asset/terrain_atlas.png");
    sceneComponents[Scene::GamePlay]->map->setMapScale("village", { 2.5f, 2.5f });
}

#ifdef _DEBUG
// Destructor implementation only in debug mode as a reminder for cleanup
Game::~Game() {
    std::cout << "Game was destroyed!" << std::endl;
}
#endif

// Handle hover events for UI elements based on the current scene
void Game::handleHover(Scene currentScene, bool isGamePaused) {
	sceneComponents[currentScene]->uiElement->updateHover();
}

// Handle button press events based on the current scene
void Game::handleButtonPress(int buttonHoverId) {
    switch (currentScene) {
    case Scene::MainMenu:
        switch (buttonHoverId) {
        case 0:
            // "Play" button pressed - switch to GamePlay scene
            sceneComponents[Scene::MainMenu]->uiElement->setColor(buttonHoverId, ElementState::Pressed);
            currentScene = Scene::GamePlay;
            sceneComponents[Scene::MainMenu]->uiElement->setColor(buttonHoverId, ElementState::Normal);
#ifdef _DEBUG
            std::cout << "Change to Gameplay scene" << std::endl;
#endif
            break;
        case 1:
            // "Setting" button pressed - switch to Setting scene
            sceneComponents[Scene::MainMenu]->uiElement->setColor(buttonHoverId, ElementState::Pressed);
            currentScene = Scene::Setting;
            sceneComponents[Scene::MainMenu]->uiElement->setColor(buttonHoverId, ElementState::Normal);
            break;
        case 2:
            // "Exit" button pressed - close the game window
            window.close();
            break;
        }
        break;
    case Scene::Setting:
        switch (buttonHoverId) {
        case 0:
            // "VOLUME" button pressed - handle volume adjustment
            sceneComponents[Scene::Setting]->uiElement->setColor(buttonHoverId, ElementState::Pressed);
            break;
        case 1:
            // "BACK" button pressed - return to MainMenu scene
            sceneComponents[Scene::Setting]->uiElement->setColor(buttonHoverId, ElementState::Pressed);
            currentScene = Scene::MainMenu;
            sceneComponents[Scene::Setting]->uiElement->setColor(buttonHoverId, ElementState::Normal);
            break;
        case 2: case 3: case 4:
            // Handle slider adjustments for volume settings
            sceneComponents[Scene::Setting]->uiElement->setThumbPosition(buttonHoverId);
            break;
        }
        break;
    case Scene::GamePlay:
        switch (buttonHoverId) {
        case 0: case 1: case 2:
            // Handle button presses in GamePlay scene
            sceneComponents[Scene::GamePlay]->uiElement->setColor(buttonHoverId, ElementState::Normal);
            break;
        }
        break;
    case Scene::PauseMenu:
        switch (buttonHoverId) {
        case 0:
            // "RESUME" button pressed - resume the game
            sceneComponents[Scene::PauseMenu]->uiElement->setColor(buttonHoverId, ElementState::Pressed);
            isGamePaused = false;
            sceneComponents[Scene::PauseMenu]->uiElement->setColor(buttonHoverId, ElementState::Normal);
            currentScene = Scene::GamePlay;
            break;
        case 1:
            // "EXIT" button pressed - exit to MainMenu scene
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
            // Close the game window if the close event is triggered
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
                // Toggle game pause state
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

        // Handle Escape key release
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Escape) {
                isEscapePressed = false;
            }
        }
	}
}

// Render the current game scene
void Game::Render() {
    // Clear the window with a specific color
    window.clear(sf::Color(199, 119, 19, 255));
    
    // Render UI elements for the current scene
	sceneComponents[currentScene]->uiElement->update();

    if (currentScene == Scene::MainMenu) {
		// Render the sprite animations for the MainMenu scene
        sceneComponents[currentScene]->spriteAnimation->updateAnimation("planet", deltaTime);
        sceneComponents[currentScene]->spriteAnimation->drawAnimation("planet");
    }

    if (currentScene == Scene::Setting) {
        sceneComponents[Scene::Setting]->uiElement->update();
    }

    if (currentScene == Scene::GamePlay) {
        sceneComponents[currentScene]->map->draw("village");

		// Render the sprite animations for the GamePlay scene
        sceneComponents[currentScene]->spriteAnimation->updateAnimation("JukkyJung", deltaTime);
        sceneComponents[currentScene]->spriteAnimation->drawAnimation("JukkyJung");
        sceneComponents[currentScene]->spriteAnimation->updateAnimation("Dummy1", deltaTime);
        sceneComponents[currentScene]->spriteAnimation->drawAnimation("Dummy1");
        sceneComponents[currentScene]->spriteAnimation->updateAnimation("Dummy2", deltaTime);
        sceneComponents[currentScene]->spriteAnimation->drawAnimation("Dummy2");
        sceneComponents[currentScene]->spriteAnimation->updateAnimation("Headman", deltaTime);
        sceneComponents[currentScene]->spriteAnimation->drawAnimation("Headman");
    }
    
    if (currentScene == Scene::PauseMenu && isGamePaused) {
		// Render the GamePlay UI elements 
        sceneComponents[Scene::GamePlay]->uiElement->update();

		// Render the sprite animations for the GamePlay scene in the background
        sceneComponents[Scene::GamePlay]->spriteAnimation->updateAnimation("JukkyJung", deltaTime);
        sceneComponents[Scene::GamePlay]->spriteAnimation->drawAnimation("JukkyJung");
        sceneComponents[Scene::GamePlay]->spriteAnimation->updateAnimation("Dummy1", deltaTime);
        sceneComponents[Scene::GamePlay]->spriteAnimation->drawAnimation("Dummy1");
        sceneComponents[Scene::GamePlay]->spriteAnimation->updateAnimation("Dummy2", deltaTime);
        sceneComponents[Scene::GamePlay]->spriteAnimation->drawAnimation("Dummy2");
        sceneComponents[Scene::GamePlay]->spriteAnimation->updateAnimation("Headman", deltaTime);
        sceneComponents[Scene::GamePlay]->spriteAnimation->drawAnimation("Headman");

		// Render the pause menu overlay
		window.draw(backgroundPauseMenu);
		window.draw(backgroundPauseMenuText);

		// Render the UI elements for the PauseMenu scene
		sceneComponents[Scene::PauseMenu]->uiElement->update();
    }
	// Display the rendered frame
	window.display();
}

// Run the game loop
void Game::GameLoop() {
    // Loop continuously while the window is open
    while (window.isOpen()) {
        // Update deltaTime to the time elapsed since the last frame
        deltaTime = clock.restart().asSeconds();
        
        // Handle input events (mouse, keyboard, etc.)
        HandleEvents();

        // Check if the current scene is GamePlay
        if (currentScene == Scene::GamePlay) {
            sf::Vector2f movement(0.f, 0.f); // Initialize movement vector

            // Check for key presses and update movement vector and animation state
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                movement.y = -100.f;
                sceneComponents[currentScene]->spriteAnimation->changeState("JukkyJung", "Walk-back");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                movement.x = -100.f;
                sceneComponents[currentScene]->spriteAnimation->changeState("JukkyJung", "Walk-left");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                movement.y = 100.f;
                sceneComponents[currentScene]->spriteAnimation->changeState("JukkyJung", "Walk-front");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                movement.x = 100.f;
                sceneComponents[currentScene]->spriteAnimation->changeState("JukkyJung", "Walk-right");
            }

            // Check for diagonal movement and update movement vector and animation state accordingly
            // Diagonal Up-Left
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                movement.x = -65.f * sqrt(2.f);
                movement.y = -65.f * sqrt(2.f);
                sceneComponents[currentScene]->spriteAnimation->changeState("JukkyJung", "Walk-left");
            }
            // Diagonal Up-Right
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                movement.x = 65.f * sqrt(2.f);
                movement.y = -65.f * sqrt(2.f);
                sceneComponents[currentScene]->spriteAnimation->changeState("JukkyJung", "Walk-right");
            }
            // Diagonal Down-Left
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                movement.x = -65.f * sqrt(2.f);
                movement.y = 65.f * sqrt(2.f);
                sceneComponents[currentScene]->spriteAnimation->changeState("JukkyJung", "Walk-left");
            }
            // Diagonal Down-Right
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                movement.x = 65.f * sqrt(2.f);
                movement.y = 65.f * sqrt(2.f);
                sceneComponents[currentScene]->spriteAnimation->changeState("JukkyJung", "Walk-right");
            }
            // If there's any movement, update the sprite's position
            if (movement.x != 0.f || movement.y != 0.f) {
                sceneComponents[currentScene]->spriteAnimation->moveSprite("JukkyJung", movement * deltaTime);
            }            
        }

        // Render the current frame
        Render();
    }
}
