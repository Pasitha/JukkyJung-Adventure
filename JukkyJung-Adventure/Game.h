#pragma once
#include "common.h"

class JukkyJung;
class Button;

class Game {
public:
	Game();

	void Update();
private:
	sf::RenderWindow m_window;
	Button* m_Button;
	JukkyJung* m_JukkyJung;
};

