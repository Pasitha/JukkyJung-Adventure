#include "Button.h"

Button::Button(sf::RenderWindow* window) : m_windowInstance(window) {
	FileManager::LoadFormFile(this->m_ButtonFont, "asset/font/ReadexPro.ttf");
	FileManager::LoadFormFile(this->m_ButtonTexture, "asset/picture/Button.png");

	m_ButtonText.setFillColor(sf::Color(0, 0, 0));
	m_ButtonText.setFont(this->m_ButtonFont);
	m_ButtonSprite.setTexture(this->m_ButtonTexture);
}

void Button::addButton(const std::string buttonLable) {
	this->m_ButtonText.setString(buttonLable);
	this->m_ButtonLable.push_back(this->m_ButtonText);

	this->m_Button.push_back(this->m_ButtonSprite);
}

void Button::setPosition(unsigned short index, sf::Vector2f position) {
	this->m_Button[index].setPosition(position);
	this->m_ButtonLable[index].setPosition({
		this->m_Button[index].getPosition().x + this->m_ButtonSprite.getGlobalBounds().width / 2.f - this->m_ButtonText.getGlobalBounds().width / 2.f,
		this->m_Button[index].getPosition().y + this->m_ButtonSprite.getGlobalBounds().height / 2.2f - this->m_ButtonText.getGlobalBounds().height / 2.2f
	});
}

void Button::isHover() {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*this->m_windowInstance);

	for (int i = 0; i < this->m_Button.size(); i++) {
		sf::Vector2f btnPosition = this->m_Button[i].getPosition();
		sf::FloatRect btnLocalBounds = this->m_Button[i].getLocalBounds();

		float btnxPosWidth = btnPosition.x + btnLocalBounds.width;
		float btnyPosHeight = btnPosition.y + btnLocalBounds.height;

		if (mousePosition.x < btnxPosWidth && mousePosition.x > btnPosition.x && mousePosition.y < btnyPosHeight && mousePosition.y > btnPosition.y) {
			this->m_Button[i].setColor(sf::Color(155, 155, 155, 155));
		}
		else {
			this->m_Button[i].setColor(sf::Color(255, 255, 255, 255));
		}
	}
}

void Button::Update() {
	for (int i = 0; i < this->m_Button.size(); i++) {
		this->m_windowInstance->draw(this->m_Button[i]);
		this->m_windowInstance->draw(this->m_ButtonLable[i]);
	}
}
