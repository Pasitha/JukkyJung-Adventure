#pragma once
#include "common.h"

class JukkyJung {
public:
	explicit JukkyJung(sf::RenderWindow* window);
	~JukkyJung();

	void ShakeAnimation();
	void Update();
private:
	static const float JUKKYJUNG_SCALE;
	static const sf::Vector2f JUKKYJUNG_POSITION;

	sf::RenderWindow* m_windowInstance;

	int m_JukkyJungHealth;
	sf::Font m_TextFont;
	sf::Text m_JukkyJungHp;

	sf::Texture m_JukkyJungTexture;
	sf::Sprite m_JukkyJungSprite;
};
