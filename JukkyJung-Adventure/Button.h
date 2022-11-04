#pragma once
#include "common.h"

class Button {
public:
	Button(sf::RenderWindow* window);

	void addButton();
	void setPosition(unsigned short index, sf::Vector2f position);
	void Update();
private:
	sf::RenderWindow* m_windowInstance;

	sf::Texture m_ButtonTexture;
	sf::Sprite m_ButtonSprite;
	sf::Text m_ButtonLable;

	std::vector<sf::Sprite> m_Button;
};
