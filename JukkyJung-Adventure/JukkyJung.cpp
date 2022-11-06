#include "JukkyJung.h"

JukkyJung::JukkyJung(sf::RenderWindow* window) : m_windowInstance(window), m_JukkyJungHealth(100) {
	FileManager::LoadFormFile(this->m_TextFont, "asset/font/ReadexPro.ttf");
	FileManager::LoadFormFile(this->m_JukkyJungTexture, "asset/picture/JukkyJung.png");
	
	m_JukkyJungHp.setFillColor(sf::Color(0, 0, 0));
	m_JukkyJungHp.setFont(this->m_TextFont);

	this->m_JukkyJungSprite.setTexture(m_JukkyJungTexture);
	this->m_JukkyJungSprite.setScale({ 0.3f, 0.3f });
	this->m_JukkyJungSprite.setPosition({ 30, 30 });
}

void JukkyJung::Update() {
	this->m_windowInstance->draw(m_JukkyJungSprite);
}
