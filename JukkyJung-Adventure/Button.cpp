#include "Button.h"

Button::Button(sf::RenderWindow* window) : m_windowInstance(window) {
	FileManager::LoadFormFile(this->m_ButtonTexture, "asset/picture/Button.png");

	m_ButtonSprite.setTexture(this->m_ButtonTexture);
}

void Button::addButton() {
	this->m_Button.push_back(this->m_ButtonSprite);
}

void Button::setPosition(unsigned short index, sf::Vector2f position) {
	this->m_Button[index].setPosition(position);
}

void Button::Update() {
	for (sf::Sprite i : m_Button)
		this->m_windowInstance->draw(i);
}
