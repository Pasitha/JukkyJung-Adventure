#pragma once
#include "common.h"

class Enemy {
public:
	Enemy(sf::RenderWindow* window);
	~Enemy();
	void Update();
private:
	sf::RenderWindow* m_windowInstance;

	int m_EnemyHealth;
	sf::Font m_TextFont;
	sf::Text m_EnemyHp;

	sf::Texture m_EnemyTexture;
	sf::Sprite m_EnemySprite;
};
