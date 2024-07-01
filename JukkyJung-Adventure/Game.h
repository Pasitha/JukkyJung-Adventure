#pragma once
#include "common.h"

// Forward declarations for classes used in Game
class UIElementManager;
class SpriteAnimation;
class MapManager;
class Character;
class Combat;

// Game class is responsible for managing the game loop, handling events, and rendering scenes.
class Game {
private:
    // Enumeration representing different scenes in the game
    enum class Scene {
        MainMenu,    // Main menu scene
        Setting,     // Setting scene
        GamePlay,    // Game play scene
        WalkingScene,// Walking scene
        Combat,      // Combat Gameplay scene
        Story,       // Cut scene and story scene
        PauseMenu    // Pause menu scene
    };

    // Struct representing game components for each scene, including Button, UIElementManager, SpriteAnimation, and Combat components
    struct SceneComponents {
        std::unique_ptr<UIElementManager> uiElement;      // UI elements manager for the scene
        std::unique_ptr<SpriteAnimation> spriteAnimation; // Sprite animation component for the scene
        std::unique_ptr<MapManager> map;                  // Map manager for the scene
        std::unique_ptr<Combat> combat;                   // Combat component for the scene
    };

public:
    // Constructor to initialize the game
    Game();

    // Destructor added only in debug mode as a reminder for cleanup
#ifdef _DEBUG
    ~Game();
#endif

public:
    // Main game loop function
    void GameLoop();

private:
    sf::RenderWindow window;                  // SFML window for rendering
    sf::View camera;                          // SFML view for camera control

    Scene currentScene;                       // Current scene in the game
    std::unordered_map<Scene, std::unique_ptr<SceneComponents>> sceneComponents;  // Map of scenes to their components
    sf::Font gameFont;                        // Font used in the game for text rendering
    bool isGamePaused;                        // Flag indicating whether the game is in a paused state
    bool isEscapePressed;                     // Flag to track if the Escape key is currently pressed
    
    sf::Text backgroundPauseMenuText;         // Text displayed in the background during pause
    sf::RectangleShape backgroundPauseMenu;   // Background shape during pause

    float deltaTime = 0.f;                    // Time elapsed between frames
    sf::Clock clock;                          // Clock for measuring time

private:
    /**
     * Handles hover events based on the current scene.
     * This function is responsible for updating button hover states.
     * @param currentScene The current scene in the game
     * @param isGamePaused Flag indicating whether the game is paused
     */
    void HandleHover(Scene currentScene, bool isGamePaused);

    /**
     * Handles button press events based on the current scene.
     * This function processes button clicks and updates the game state accordingly.
     * @param buttonHoverId ID of the button that was pressed
     */
    void HandleButtonPress(int buttonHoverId);

    /**
     * Handles player movement in the GamePlay scene.
     * This function updates the player's position based on input.
     */
    void HandlePlayerMovement();

    /**
     * Handles user input events.
     * This function processes input from the user, such as keyboard and mouse events.
     */
    void HandleEvents();

    /**
     * Updates the camera position and settings based on the current game state.
     * This function ensures the camera follows the player or other target.
     */
    void UpdateCamera();

    /**
     * Renders the current state of the game.
     * This function draws all game objects to the window.
     */
    void Render();
};
