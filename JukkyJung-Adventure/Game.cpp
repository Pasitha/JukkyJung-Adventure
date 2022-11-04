#include "common.h"

Game::Game() : m_window(sf::VideoMode(1920, 1080), "JukkyJuung Adventure", sf::Style::Default) {
	this->m_window.setFramerateLimit(60);

	this->m_Button = new Button(&this->m_window);
	this->m_JukkyJung = new JukkyJung(&this->m_window);

	m_Button->addButton();
	m_Button->addButton();
	m_Button->setPosition(0, { 50, 50 });
	m_Button->setPosition(1, { 500, 500 });
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
		this->m_Button->Update();
		this->m_JukkyJung->Update();
		this->m_window.display();
	}
}
