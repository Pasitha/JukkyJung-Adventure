#include "common.h"

Game::Game() : m_window(sf::VideoMode(1920, 1080), "JukkyJuung Adventure", sf::Style::Default), m_gameScene(m_Scene::mainMenu) {
	this->m_window.setFramerateLimit(60);

	this->m_SceneComponent[m_Scene::mainMenu] = {
		new Button(&this->m_window)
	};

	this->m_SceneComponent[m_Scene::gamePlay] = {
		new Button(&this->m_window),
		new JukkyJung(&this->m_window)
	};
	
	this->m_SceneComponent[m_Scene::mainMenu].m_Button->addButton("Play");
	this->m_SceneComponent[m_Scene::mainMenu].m_Button->addButton("Setting");
	this->m_SceneComponent[m_Scene::mainMenu].m_Button->addButton("Exit");
	this->m_SceneComponent[m_Scene::mainMenu].m_Button->setPosition(0, { 50, 300 });
	this->m_SceneComponent[m_Scene::mainMenu].m_Button->setPosition(1, { 50, 500 });
	this->m_SceneComponent[m_Scene::mainMenu].m_Button->setPosition(2, { 50, 700 });

	this->m_SceneComponent[m_Scene::gamePlay].m_Button->addButton("ATTACK");
	this->m_SceneComponent[m_Scene::gamePlay].m_Button->addButton("ITEM");
	this->m_SceneComponent[m_Scene::gamePlay].m_Button->addButton("SKIP ROUND");
	this->m_SceneComponent[m_Scene::gamePlay].m_Button->setPosition(0, { 50, 800 });
	this->m_SceneComponent[m_Scene::gamePlay].m_Button->setPosition(1, { 400, 800 });
	this->m_SceneComponent[m_Scene::gamePlay].m_Button->setPosition(2, { 750, 800 });
}

void Game::Update() {
	while (this->m_window.isOpen()) {
		sf::Event event;
		while (this->m_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				this->m_window.close();
			}
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
		}

		this->m_window.clear();
		switch (m_gameScene) {
			case m_Scene::mainMenu:
				this->m_SceneComponent[m_Scene::mainMenu].m_Button->Update();
				break;
			case m_Scene::setting:

				break;
			case m_Scene::gamePlay:
				this->m_SceneComponent[m_Scene::gamePlay].m_Button->Update();
				this->m_SceneComponent[m_Scene::gamePlay].m_JukkyJung->Update();
				break;
		}
		this->m_window.display();
	}
}
