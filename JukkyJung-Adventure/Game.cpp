#include "common.h"

Game::Game() : m_window(sf::VideoMode(1920, 1080), "JukkyJuung Adventure", sf::Style::Default) {
	this->m_window.setFramerateLimit(60);

	m_Scene Scene = m_Scene::mainMenu;

	this->m_Button = new Button(&this->m_window);
	this->m_JukkyJung = new JukkyJung(&this->m_window);

	this->m_Button->addButton("Test Button 1");
	this->m_Button->addButton("Test Button 2");
	this->m_Button->addButton("Test Button 3");
	this->m_Button->setPosition(0, { 50, 800 });
	this->m_Button->setPosition(1, { 400, 800 });
	this->m_Button->setPosition(2, { 750, 800 });
}

void Game::Update() {
	while (this->m_window.isOpen()) {
		sf::Event event;
		while (this->m_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				this->m_window.close();
			}
			if (event.type == sf::Event::MouseMoved) {
				this->m_Button->isHover();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				std::cout << this->m_Button->whichButtonHover() << std::endl;
			}
		}

		this->m_window.clear();
		this->m_Button->Update();
		this->m_JukkyJung->Update();
		this->m_window.display();
	}
}
