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
    sceneComponents[Scene::MainMenu]->button = std::make_unique<Button>(&window);
    sceneComponents[Scene::Setting]->button = std::make_unique<Button>(&window);
    sceneComponents[Scene::GamePlay]->button = std::make_unique<Button>(&window);
    sceneComponents[Scene::GamePlay]->character = std::make_unique<Character>(&window);
    sceneComponents[Scene::PauseMenu]->button = std::make_unique<Button>(&window);
    
    // Initialize asset manager for each scene
    sceneComponents[Scene::MainMenu]->spriteAnimation = std::make_unique<SpriteAnimation>(&window);

    sceneComponents[Scene::MainMenu]->spriteAnimation->loadSpriteSheet("asset/JukkyJung-Sprite.png", { 64, 64 }, 24);
    sceneComponents[Scene::MainMenu]->spriteAnimation->setScale({ 2.5f, 2.5f });
    sceneComponents[Scene::MainMenu]->spriteAnimation->setState("Idel", 3, 7, .35f);
    sceneComponents[Scene::MainMenu]->spriteAnimation->changeState("Idel");

    sceneComponents[Scene::GamePlay]->character->addCharacter("JukkyJung", 120, 10, ElementalPower::Time, "asset/picture/JukkyJung.png");
    sceneComponents[Scene::GamePlay]->character->addCharacter("Evil JukkyJung", 120, 10, ElementalPower::Time, "asset/picture/JukkyJung.png");

    // Initialize scene components with buttons and their positions
    InitializeSceneComponents(Scene::MainMenu, { {"Play", {50, 300}}, {"Setting", {50, 500}}, {"Exit", {50, 700}} });
    InitializeSceneComponents(Scene::Setting, { {"VOLUME", {50, 300}}, {"BACK", {50, 500}} });
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
                int buttonHoverId = sceneComponents[Scene::MainMenu]->button->whichButtonHover();

                switch (buttonHoverId) {
                case 0:
                    sceneComponents[Scene::MainMenu]->button->setDefaultColor(buttonHoverId);
                    currentScene = Scene::GamePlay;
                    break;
                case 1:
                    sceneComponents[Scene::MainMenu]->button->setDefaultColor(buttonHoverId);
                    currentScene = Scene::Setting;
                    break;
                case 2:
                    window.close();
                    break;
                }
            }
            break;

        case Scene::Setting:
            // Handle events for the settings scene
            if (event.type == sf::Event::MouseMoved) {
                sceneComponents[Scene::Setting]->button->isHover();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                int buttonHoverId = sceneComponents[Scene::Setting]->button->whichButtonHover();

                switch (buttonHoverId) {
                case 0:
                    sceneComponents[Scene::MainMenu]->button->setDefaultColor(buttonHoverId);
                    break;
                case 1:
                    sceneComponents[Scene::Setting]->button->setDefaultColor(buttonHoverId);
                    currentScene = Scene::MainMenu;
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
				int ButtonHoverId = sceneComponents[Scene::PauseMenu]->button->whichButtonHover();

				switch (ButtonHoverId) {
				case 0:
					// sceneComponents[Scene::GamePlay]->character->ShakeAnimation()
					sceneComponents[Scene::PauseMenu]->button->setDefaultColor(ButtonHoverId);
                    // sceneComponents[Scene::Combat]->combat->PerformAttack(playerCharacter, enemyCharacter); // Assuming playerCharacter and enemyCharacter are available
					break;
				case 1:
					// Handle ITEM button press
					sceneComponents[Scene::PauseMenu]->button->setDefaultColor(ButtonHoverId);
					break;
				case 2:
					// Handle SKIP ROUND button press
					sceneComponents[Scene::PauseMenu]->button->setDefaultColor(ButtonHoverId);
					break;
				}

				if (isGamePaused) {
                    int ButtonHoverId = sceneComponents[Scene::PauseMenu]->button->whichButtonHover();
					switch (ButtonHoverId) {
					case 0:
						isGamePaused = false;
                        sceneComponents[Scene::PauseMenu]->button->setDefaultColor(ButtonHoverId);
						break;
					case 1:
						isGamePaused = false;
                        sceneComponents[Scene::PauseMenu]->button->setDefaultColor(ButtonHoverId);
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

    if (currentScene != Scene::GamePlay) {
        // Render the button on currentScene
        sceneComponents[currentScene]->button->update();
        sceneComponents[currentScene]->spriteAnimation->updateAnimation(deltaTime);
        sceneComponents[currentScene]->spriteAnimation->drawAnimation({1000, 100});
    }
    else {
		// Render the game play scene
		sceneComponents[Scene::GamePlay]->button->update();
		sceneComponents[Scene::GamePlay]->character->draw("JukkyJung");


		if (isGamePaused) {
			// Render the pause menu when the game is paused
			window.draw(backgroundPauseMenu);
			window.draw(backgroundPauseMenuText);

			sceneComponents[Scene::PauseMenu]->button->update();
		}
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
