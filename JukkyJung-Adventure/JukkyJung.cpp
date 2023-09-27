#include "JukkyJung.h"

JukkyJung::JukkyJung(sf::RenderWindow* window) : m_windowInstance(window), m_JukkyJungHealth(100) {
	FileManager::LoadFormFile(this->m_TextFont, "asset/font/ReadexPro.ttf");
	FileManager::LoadFormFile(this->m_JukkyJungTexture, "asset/picture/JukkyJung.png");
	
	m_JukkyJungHp.setFillColor(sf::Color(255, 255, 255));
	m_JukkyJungHp.setFont(this->m_TextFont);
	m_JukkyJungHp.setString("HP: 100");

	this->m_JukkyJungSprite.setTexture(m_JukkyJungTexture);
	this->m_JukkyJungSprite.setScale({ 0.3f, 0.3f });
	this->m_JukkyJungSprite.setPosition({ 30, 30 });
}

// Shake animation method has a thread problem
// try to animate without sleep main thread
void JukkyJung::ShakeAnimation() {
	sf::Vector2f beforeShakeAnimationPosition = this->m_JukkyJungSprite.getPosition();
	for (int i = 0; i < 10; i++) {
		this->m_JukkyJungSprite.move({ 2 - (float)std::pow(-1, i) * 4, 0 });
		std::this_thread::sleep_for(std::chrono::milliseconds(45));

		this->m_windowInstance->draw(this->m_JukkyJungSprite);	
		this->m_windowInstance->display();
	}

	this->m_JukkyJungSprite.setPosition(beforeShakeAnimationPosition);
	this->m_windowInstance->draw(this->m_JukkyJungSprite);
	this->m_windowInstance->display();
}

void JukkyJung::Update() {
	this->m_windowInstance->draw(m_JukkyJungHp);
	this->m_windowInstance->draw(m_JukkyJungSprite);
}
