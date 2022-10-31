#pragma once
#include "common.h"

class JukkyJung;

class Game {
public:
	Game();

	void Update();
private:
	sf::RenderWindow m_window;
	JukkyJung* m_JukkyJung;
};

