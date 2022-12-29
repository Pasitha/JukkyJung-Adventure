#pragma once
#include "common.h"

class Button;
class JukkyJung;
class Enemy;

class Game {
public:
	Game();

	void Update();
private:
	sf::RenderWindow m_window;

	enum class m_Scene {
		mainMenu,
		setting,
		gamePlay
	};

	struct m_gameComponent {
		Button* m_Button;
		JukkyJung* m_JukkyJung;
		Enemy* m_Enemy;
	};

	m_Scene m_gameScene;
	std::unordered_map<m_Scene, m_gameComponent> m_SceneComponent;

	sf::Text m_backgroundPauseMenuText;
	sf::RectangleShape m_backgroundPauseMenu;
};
