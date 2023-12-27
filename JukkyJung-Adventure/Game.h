#pragma once
#include "common.h"

// Forward declarations for classes used in Game
class Button;
class JukkyJung;
class Enemy;
class Character;

// Game class is responsible for managing the game loop, handling events, and rendering scenes.
class Game {
private:
    // Enumeration representing different scenes in the game
    enum class Scene {
        MainMenu,    // Main menu scene
        Setting,     // Setting scene (not yet implemented)
        GamePlay,    // Game play scene
        PauseMenu    // Pause menu scene
    };

    // Enumeration representing different state in GamePlay Scene
    enum class GameState {
        Walking,
        Combat,
        Story
    };

    // Struct representing game components for each scene such that Button, JukkyJug character, and Enemy character component
    struct SceneComponents {
        std::unique_ptr<Button> button;
        std::unique_ptr<Character> character;
    };

public:
    // Constructor to initialize the game
    Game();

    // Destructor added only in debug mode as a reminder for cleanup
#ifdef _DEBUG
    ~Game();
#endif

    // Function to handle user input events
    void HandleEvents();
    // Function to render the current state of the game
    void Render();
    // Main game loop function
    void GameLoop();

private:
    sf::RenderWindow window;                  // SFML window for rendering
    Scene currentScene;                       // Current scene in the game
    GameState currentGameState;               // Current GameState in the GamePlay Scene
    std::unordered_map<Scene, std::unique_ptr<SceneComponents>> sceneComponents;  // Map of scenes to their components
    sf::Font gameFont;                        // Font used in the game for text rendering
    bool isGamePaused;                        // Flag indicating whether the game is in a paused state
    sf::Text backgroundPauseMenuText;         // Text displayed in the background during pause
    sf::RectangleShape backgroundPauseMenu;   // Background shape during pause

    // Function to initialize components for a specific scene with buttons and positions
    void InitializeSceneComponents(Scene scene, const std::vector<std::pair<std::string, sf::Vector2f>>& buttons);
};
