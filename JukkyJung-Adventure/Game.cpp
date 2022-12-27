#include "common.h"

Game::Game() : m_window(sf::VideoMode(1920, 1080), "JukkyJuung Adventure", sf::Style::Default), m_gameScene(m_Scene::mainMenu) {
	this->m_window.setFramerateLimit(60);

	this->m_SceneComponent[m_Scene::mainMenu] = {
		new Button(&this->m_window)
	};

	this->m_SceneComponent[m_Scene::gamePlay] = {
		new Button(&this->m_window),
		new JukkyJung(&this->m_window),
		new Enemy(&this->m_window)
	};
	
	this->m_SceneComponent[m_Scene::mainMenu].m_Button->addButton("Play", { 50, 300 });
	this->m_SceneComponent[m_Scene::mainMenu].m_Button->addButton("Setting", { 50, 500 });
	this->m_SceneComponent[m_Scene::mainMenu].m_Button->addButton("Exit", { 50, 700 });

	this->m_SceneComponent[m_Scene::gamePlay].m_Button->addButton("ATTACK", { 50, 800 });
	this->m_SceneComponent[m_Scene::gamePlay].m_Button->addButton("ITEM", { 400, 800 });
	this->m_SceneComponent[m_Scene::gamePlay].m_Button->addButton("SKIP ROUND", { 750, 800 });
}

void Game::Update() {
	while (this->m_window.isOpen()) {
		sf::Event event;
		while (this->m_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				this->m_window.close();
			}

			switch (m_gameScene) {
			case m_Scene::mainMenu:
				if (event.type == sf::Event::MouseMoved) {
					this->m_SceneComponent[m_Scene::mainMenu].m_Button->isHover();
				}
				if (event.type == sf::Event::MouseButtonPressed) {
					switch (this->m_SceneComponent[m_Scene::mainMenu].m_Button->whichButtonHover()) {
					case 0:
						this->m_gameScene = m_Scene::gamePlay;
						break;
					case 1:
						this->m_gameScene = m_Scene::setting;
						break;
					case 2:
						this->m_window.close();
						break;
					}
				}
				break;
			case m_Scene::gamePlay:
				if (event.type == sf::Event::MouseMoved) {
					this->m_SceneComponent[m_Scene::gamePlay].m_Button->isHover();
				}
				if (event.type == sf::Event::MouseButtonPressed) {
					switch (this->m_SceneComponent[m_Scene::gamePlay].m_Button->whichButtonHover()) {
					case 0:
						break;
					case 1:
						break;
					case 2:
						break;
					}
				}
				break;
			}
		}

		this->m_window.clear(sf::Color(199, 119, 19, 255));
		switch (m_gameScene) {
			case m_Scene::mainMenu:
				this->m_SceneComponent[m_Scene::mainMenu].m_Button->Update();
				break;
			case m_Scene::setting:

				break;
			case m_Scene::gamePlay:
				this->m_SceneComponent[m_Scene::gamePlay].m_Button->Update();
				this->m_SceneComponent[m_Scene::gamePlay].m_JukkyJung->Update();
				this->m_SceneComponent[m_Scene::gamePlay].m_Enemy->Update();
				break;
		}
		this->m_window.display();
	}
}
