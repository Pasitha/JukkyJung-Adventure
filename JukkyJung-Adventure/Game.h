#pragma once
#include "common.h"

class Button;
class JukkyJung;
class Enemy;

class Game {
private:
	enum class Scene {
		mainMenu,
		setting,
		gamePlay,
		pauseMenu
	};

	struct m_gameComponent {
		std::unique_ptr<Button> m_Button;
		std::unique_ptr<JukkyJung> m_JukkyJung;
		std::unique_ptr<Enemy> m_Enemy;
	};

public:
	Game();

	void HandleEvents();
	void Render();
	void GameLoop();

private:
	sf::RenderWindow m_window;

	Scene m_gameScene;
	std::unordered_map<Scene, std::unique_ptr<m_gameComponent>> m_SceneComponent;

	sf::Font m_gameFont;

	bool m_isGamePause;
	sf::Text m_backgroundPauseMenuText;
	sf::RectangleShape m_backgroundPauseMenu;

	void initializeSceneComponent(Scene scene, const std::vector<std::pair<std::string, sf::Vector2f>>& buttons);
};
