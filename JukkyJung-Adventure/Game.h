#pragma once
#include "common.h"
#include "Scene.h"
#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>

// Forward declarations for scene classes to avoid circular dependencies
class MainMenuScene;
class GamePlayScene;
class SettingScene;
class PauseMenuScene;

/**
 * @class Game
 * @brief The main engine of the game.
 *
 * This class is responsible for initializing the game, managing the game loop,
 * handling scene transitions, and holding global game resources like the window and fonts.
 * It follows the Singleton pattern to ensure that there is only one instance of the game engine.
 */
class Game {
public:
    /**
     * @brief Constructs the Game object.
     * Initializes the window, renderer, loads global assets, and sets up the scene manager.
     */
    Game();
    ~Game();

    /**
     * @brief Provides access to the single instance of the Game class.
     * @return A pointer to the Game instance.
     */
    static Game* getInstance();

    /**
     * @brief Starts and runs the main game loop.
     */
    void run();

    /**
     * @brief Changes the current active scene.
     * @param sceneType The type of the scene to switch to.
     */
    void changeScene(Scene::Type sceneType);

    /**
     * @brief Provides access to the main render window.
     * @return A reference to the sf::RenderWindow.
     */
    sf::RenderWindow& getWindow() { return window; }

    /**
     * @brief Provides access to the global game font.
     * @return A constant reference to the sf::Font.
     */
    const sf::Font& getFont() const { return gameFont; }

    /**
     * @brief Retrieves a specific scene from the scene manager.
     * @param sceneType The type of the scene to retrieve.
     * @return A pointer to the requested Scene object.
     */
    Scene* getScene(Scene::Type sceneType);

private:
    /**
     * @brief Handles all SFML events, polling them from the window.
     */
    void handleEvents();

    /**
     * @brief Updates the current scene's logic.
     * @param deltaTime The time elapsed since the last frame.
     */
    void update(sf::Time deltaTime);

    /**
     * @brief Renders the current scene to the window.
     */
    void render();

    sf::RenderWindow window; ///< The main render window.
    sf::Font gameFont;       ///< The global font used throughout the game.
    Renderer renderer;       ///< The renderer responsible for all drawing operations.

    std::unordered_map<Scene::Type, std::unique_ptr<Scene>> scenes; ///< A map holding all game scenes.
    Scene* currentScene;     ///< A pointer to the currently active scene.

    static Game* instance;   ///< The static instance of the Game class for the Singleton pattern.
};
