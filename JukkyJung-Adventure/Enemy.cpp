#include "Enemy.h"

Enemy::Enemy(sf::RenderWindow* window) : m_windowInstance(window), m_EnemyHealth(100) {
	std::cout << "Enemy Create!" << std::endl;
	FileManager::LoadFromFile(this->m_TextFont, "asset/font/ReadexPro.ttf");
	FileManager::LoadFromFile(this->m_EnemyTexture, "asset/picture/MonsterJukkyJung.png");
	
	m_EnemyHp.setFillColor(sf::Color(255, 255, 255));
	m_EnemyHp.setFont(this->m_TextFont);
	m_EnemyHp.setString("HP: 100");
	m_EnemyHp.setPosition({ 1800, 0 });

	this->m_EnemySprite.setTexture(this->m_EnemyTexture);
	this->m_EnemySprite.setScale({ 0.3f, 0.3f });
	this->m_EnemySprite.setPosition({ 1200, 30 });
}

// Destructor implementation only in debug mode
#ifdef _DEBUG
Enemy::~Enemy(){
	std::cout << "Enemy was destroy!" << std::endl;
}
#endif

void Enemy::Update() {
	this->m_windowInstance->draw(this->m_EnemySprite);
	this->m_windowInstance->draw(this->m_EnemyHp);
}
