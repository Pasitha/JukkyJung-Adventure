#pragma once
#include "common.h"

// Forward declarations for classes used in Game
class Button;
class UIElementManager;
class SpriteAnimation;
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
        std::unique_ptr<UIElementManager> uiElement;    // UI elements manager for the scene
        std::unique_ptr<SpriteAnimation> spriteAnimation; // Sprite animation component for the scene
        std::unique_ptr<Combat> combat;                 // Combat component for the scene
    };

public:
    // Constructor to initialize the game
    Game();

    // Destructor added only in debug mode as a reminder for cleanup
#ifdef _DEBUG
    ~Game();
#endif
private:
    /**
     * Handles hover events based on the current scene.
     * This function is responsible for updating button hover states.
     */
    void handleHover(Scene currentScene, bool isGamePaused);

    /**
     * Handles button press events based on the current scene.
     * This function processes button clicks and updates the game state accordingly.
     */
    void handleButtonPress(int buttonHoverId);

public:
    // Function to handle user input events
    void HandleEvents();
    // Function to render the current state of the game
    void Render();
    // Main game loop function
    void GameLoop();

private:
    sf::RenderWindow window;                  // SFML window for rendering
    Scene currentScene;                       // Current scene in the game
    std::unordered_map<Scene, std::unique_ptr<SceneComponents>> sceneComponents;  // Map of scenes to their components
    sf::Font gameFont;                        // Font used in the game for text rendering
    bool isGamePaused;                        // Flag indicating whether the game is in a paused state
    bool isEscapePressed;                     // Flag to track if the Escape key is currently pressed

    sf::Sprite settingPanel;                  // Sprite for the settings panel
    sf::Sprite volumeSlider;                  // Sprite for the volume slider
    sf::Sprite horizontalSlider;              // Sprite for the horizontal slider
    sf::Sprite musicCheckBox;                 // Sprite for the music checkbox
    sf::Sprite effectCheckBox;                // Sprite for the effects checkbox

    sf::Texture settingPanelTexture;          // Texture for the settings panel
    sf::Texture volumeSliderTexture;          // Texture for the volume slider
    sf::Texture horizontalSliderTexture;      // Texture for the horizontal slider
    sf::Texture musicCheckBoxTexture;         // Texture for the music checkbox
    sf::Texture effectCheckBoxTexture;        // Texture for the effects checkbox
    
    sf::Text backgroundPauseMenuText;         // Text displayed in the background during pause
    sf::RectangleShape backgroundPauseMenu;   // Background shape during pause

    float deltaTime = 0.f;                    // Time elapsed between frames
    sf::Clock clock;                          // Clock for measuring time

private:
    /**
     * Function to initialize components for a specific scene with buttons and positions.
     * @param scene The scene to initialize components for.
     * @param buttons A vector of pairs, each containing a button label and its position.
     */
    void InitializeSceneComponents(Scene scene, const std::vector<std::pair<std::string, sf::Vector2f>>& buttons);
};
