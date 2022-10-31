#include "JukkyJung.h"

JukkyJung::JukkyJung(sf::RenderWindow* window) : m_windowInstance(window), m_JukkyJungHealth(100) {
	FileManager::LoadFormFile(this->m_JukkyJungTexture, "asset/picture/JukkyJung.png");
	
	this->m_JukkyJungSprite.setTexture(m_JukkyJungTexture);
}

void JukkyJung::Update() {
	this->m_windowInstance->draw(m_JukkyJungSprite);
}
