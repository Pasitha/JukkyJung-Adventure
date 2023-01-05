#pragma once
#include "common.h"

class Button;
class JukkyJung;
class Enemy;

class Game {
public:
	Game();

	void run();
private:
	sf::RenderWindow m_window;

	enum class m_Scene {
		mainMenu,
		setting,
		gamePlay,
		pauseMenu
	};

	struct m_gameComponent {
		Button* m_Button;
		JukkyJung* m_JukkyJung;
		Enemy* m_Enemy;
	};

	m_Scene m_gameScene;
	std::unordered_map<m_Scene, m_gameComponent> m_SceneComponent;

	sf::Font m_gameFont;

	bool m_isGamePause;
	sf::Text m_backgroundPauseMenuText;
	sf::RectangleShape m_backgroundPauseMenu;
private:
	void inputHandler();
	void update();
};
