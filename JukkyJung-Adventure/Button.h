#pragma once
#include "common.h"

class Button {
public:
	Button(sf::RenderWindow* window);
	// Add a destructor only in debug mode
#ifdef _DEBUG
	~Button();
#endif

	void addButton(const std::string buttonLable, sf::Vector2f buttonPosition);
	void setPosition(unsigned short buttonID, sf::Vector2f position);
	void isHover();
	int whichButtonHover();
	void enableButton();
	void disableButton();

	void Update();
private:
	static const sf::Color NORMAL_COLOR;
	static const sf::Color HOVER_COLOR;

	static const int COLOR_ALPHA_NORMAL = 255;
	static const int COLOR_ALPHA_HOVER = 155;

	unsigned int m_numberOfButtons;
	sf::RenderWindow* m_windowInstance;

	sf::Font m_ButtonFont;
	sf::Texture m_ButtonTexture;
	sf::Sprite m_ButtonSprite;
	sf::Text m_ButtonText;

	std::vector<sf::Sprite> m_Button;
	std::vector<sf::Text> m_ButtonLable;
};
