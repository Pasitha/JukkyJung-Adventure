#pragma once
#include "common.h"

class JukkyJung {
public:
	JukkyJung(sf::RenderWindow* window);

	void Update();
private:
	sf::RenderWindow* m_windowInstance;

	sf::Font m_TextFont;

	int m_JukkyJungHealth;
	sf::Text m_JukkyJungHp;
	sf::Texture m_JukkyJungTexture;
	sf::Sprite m_JukkyJungSprite;
};
