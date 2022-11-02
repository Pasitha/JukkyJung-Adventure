#pragma once
#include "common.h"

class JukkyJung {
public:
	JukkyJung(sf::RenderWindow* window);

	void Update();
private:
	sf::RenderWindow* m_windowInstance;

	int m_JukkyJungHealth;
	sf::Texture m_JukkyJungTexture;
	sf::Sprite m_JukkyJungSprite;
};
