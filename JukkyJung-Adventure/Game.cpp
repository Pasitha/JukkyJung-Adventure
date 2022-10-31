#include "common.h"

Game::Game() : m_window(sf::VideoMode(1920, 1080), "JukkyJuung Adventure", sf::Style::Default) {
	this->m_window.setFramerateLimit(60);

	this->m_JukkyJung = new JukkyJung(&this->m_window);
}

void Game::Update() {
	while (this->m_window.isOpen()) {
		sf::Event event;
		while (this->m_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				this->m_window.close();
			}
		}

		this->m_window.clear();
		this->m_JukkyJung->Update();
		this->m_window.display();
	}
}
