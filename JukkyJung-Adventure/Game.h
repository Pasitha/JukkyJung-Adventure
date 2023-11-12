#pragma once
#include "common.h"

// Forward declarations for classes used in Game
class Button;
class JukkyJung;
class Enemy;

// Game class is responsible for managing the game loop, handling events, and rendering scenes.
class Game {
private:
	// Enumeration representing different scenes in the game
	enum class Scene {
		mainMenu,
		setting,
		gamePlay,
		pauseMenu
	};

	// Struct representing game components for each scene such that Button, JukkyJug character and Enemy character component
	struct m_gameComponent {
		std::unique_ptr<Button> m_Button;
		std::unique_ptr<JukkyJung> m_JukkyJung;
		std::unique_ptr<Enemy> m_Enemy;
	};

public:
	Game();

	// Function to handle user input events
	void HandleEvents();
	// Function to render the current state of the game
	void Render();
	// Main game loop function
	void GameLoop();

private:
	sf::RenderWindow m_window;                  // SFML window for rendering

    Scene m_gameScene;                          // Current scene in the game
    std::unordered_map<Scene, std::unique_ptr<m_gameComponent>> m_SceneComponent;  // Map of scenes to their components

    sf::Font m_gameFont;                        // Font used in the game for text rendering

    bool m_isGamePause;                         // Flag indicating whether the game is in a paused state
    sf::Text m_backgroundPauseMenuText;         // Text displayed in the background during pause
    sf::RectangleShape m_backgroundPauseMenu;   // Background shape during pause

    // Function to initialize components for a specific scene with buttons and positions
    void initializeSceneComponent(Scene scene, const std::vector<std::pair<std::string, sf::Vector2f>>& buttons);
};
