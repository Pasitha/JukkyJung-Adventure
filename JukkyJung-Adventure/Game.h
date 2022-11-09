#pragma once
#include "common.h"

class Button;
class JukkyJung;

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

	Button* m_Button;
	JukkyJung* m_JukkyJung;
};
