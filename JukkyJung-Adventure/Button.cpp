#include "Button.h"

Button::Button(sf::RenderWindow* window) : m_windowInstance(window) {
	FileManager::LoadFormFile(this->m_ButtonTexture, "asset/picture/JukkyJung.png");

	m_ButtonSprite.setTexture(this->m_ButtonTexture);
}

void Button::Update() {
	this->m_windowInstance->draw(this->m_ButtonSprite);
}
