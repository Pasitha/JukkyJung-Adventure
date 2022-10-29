#pragma once
#include "common.h"

class Game {
public:
	Game();

	void Update();
private:
	sf::RenderWindow m_window;
};

auto render = [](sf::RenderWindow* window) -> void {
	window->setActive(true);
	sf::CircleShape shape(100.f);

	while (window->isOpen()) {
		window->clear();
		window->draw(shape);
		window->display();
	}
};
