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

    FileManager::LoadFromFile(settingPanelTexture, "asset/UI/PNG/grey_panel.png");
    FileManager::LoadFromFile(volumeSliderTexture, "asset/UI/PNG/grey_sliderDown.png");
    FileManager::LoadFromFile(horizontalSliderTexture, "asset/UI/PNG/grey_sliderHorizontal.png");
    FileManager::LoadFromFile(musicCheckBoxTexture, "asset/UI/PNG/grey_box.png");
    FileManager::LoadFromFile(effectCheckBoxTexture, "asset/UI/PNG/grey_box.png");

    settingPanel.setTexture(settingPanelTexture);
    volumeSlider.setTexture(volumeSliderTexture);
    horizontalSlider.setTexture(horizontalSliderTexture);
    musicCheckBox.setTexture(musicCheckBoxTexture);
    effectCheckBox.setTexture(effectCheckBoxTexture);

    settingPanel.setPosition({ 500, 200 });  // Adjust position as needed
    settingPanel.setScale({ 3.f, 3.f });      // Adjust scale as needed

    volumeSlider.setPosition({ 600, 350 });   // Adjust position as needed
    volumeSlider.setScale({ 1.f, 1.f });       // Adjust scale as needed

    horizontalSlider.setPosition({ 600, 375 }); // Adjust position as needed
    horizontalSlider.setScale({ 1.f, 1.f });    // Adjust scale as needed

    musicCheckBox.setPosition({ 600, 650 });   // Adjust position as needed
    musicCheckBox.setScale({ 1.f, 1.f });       // Adjust scale as needed

    effectCheckBox.setPosition({ 800, 650 });  // Adjust position as needed
    effectCheckBox.setScale({ 1.f, 1.f });       // Adjust scale as needed

	// settingPanel.setPosition({ 1250, 450 });
    settingPanel.setScale({ 5.f, 5.f });

    // volumeSlider.setPosition({ 1275, 550 });
    volumeSlider.setScale({ 1.25f , 1.25f });

    // horizontalSlider.setPosition({ 1275, 550 });
    horizontalSlider.setScale({ 1.5f, 1.5f });

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

    sceneComponents[Scene::MainMenu]->spriteAnimation->loadSpriteSheet("asset/Planet-Sprite.png", { 256, 256 }, 1);
    sceneComponents[Scene::MainMenu]->spriteAnimation->setScale({ 2.5f, 2.5f });
    sceneComponents[Scene::MainMenu]->spriteAnimation->setState("Idel", 0, 50, .10f);
    sceneComponents[Scene::MainMenu]->spriteAnimation->changeState("Idel");

    sceneComponents[Scene::GamePlay]->spriteAnimation->loadSpriteSheet("asset/JukkyJung-Sprite.png", { 64, 64 }, 24);
    sceneComponents[Scene::GamePlay]->spriteAnimation->setScale({ 2.5f, 2.5f });
    sceneComponents[Scene::GamePlay]->spriteAnimation->setState("Idel-left", 3, 7, .35f);
    sceneComponents[Scene::GamePlay]->spriteAnimation->changeState("Idel-left");

    // Initialize scene components with buttons and their positions
    sceneComponents[Scene::MainMenu]->uiElement->addButton({ {"Play", {150, 300}}, {"Setting", {150, 500}}, {"Exit", {150, 700}} }, TextAlignment::Center);
    sceneComponents[Scene::Setting]->uiElement->addButton({ {"VOLUME", {50, 300}}, {"BACK", {50, 500}} }, TextAlignment::Center);
    sceneComponents[Scene::GamePlay]->uiElement->addButton({ {"ATTACK", {50, 800}}, {"ITEM", {400, 800}}, {"SKIP ROUND", {750, 800}} }, TextAlignment::Center);
    sceneComponents[Scene::PauseMenu]->uiElement->addButton({ {"RESUME", {850, 300}}, {"EXIT", {850, 500}} }, TextAlignment::Center);

    sceneComponents[Scene::Setting]->uiElement->addSlider("VOLUME", { 600, 350 }, { 100, 5 });
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
            if (event.key.code == sf::Keyboard::Escape && !isEscapePressed) {
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
        sceneComponents[currentScene]->spriteAnimation->drawAnimation({1000, 220});
    }

    if (currentScene == Scene::Setting) {
        window.draw(settingPanel);
        window.draw(horizontalSlider);
        window.draw(volumeSlider);
        window.draw(musicCheckBox);
        window.draw(effectCheckBox);
    }
    
    if (currentScene == Scene::PauseMenu && isGamePaused) {
		// Render the button on currentScene
		sceneComponents[Scene::GamePlay]->uiElement->update();

		// Render the spriteAnimation on currentScene
        sceneComponents[Scene::GamePlay]->spriteAnimation->updateAnimation(deltaTime);
        sceneComponents[Scene::GamePlay]->spriteAnimation->drawAnimation({1000, 220});

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
