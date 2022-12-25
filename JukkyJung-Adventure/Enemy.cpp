#include "Enemy.h"

Enemy::Enemy(sf::RenderWindow* window) : m_windowInstance(window), m_EnemyHealth(100) {
	FileManager::LoadFormFile(this->m_TextFont, "asset/font/ReadexPro.ttf");
	FileManager::LoadFormFile(this->m_EnemyTexture, "asset/picture/MonsterJukkyJung.png");
	
	m_EnemyHp.setFillColor(sf::Color(255, 255, 255));
	m_EnemyHp.setFont(this->m_TextFont);
	m_EnemyHp.setString("HP: 100");
	m_EnemyHp.setPosition({ 1800, 0 });

	this->m_EnemySprite.setTexture(m_EnemyTexture);
	this->m_EnemySprite.setScale({ 0.3f, 0.3f });
	this->m_EnemySprite.setPosition({ 1200, 30 });
}

void Enemy::Update() {
	this->m_windowInstance->draw(m_EnemySprite);
	this->m_windowInstance->draw(m_EnemyHp);
}
