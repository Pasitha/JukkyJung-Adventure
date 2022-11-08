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
	Button* m_Button;
	JukkyJung* m_JukkyJung;
};
