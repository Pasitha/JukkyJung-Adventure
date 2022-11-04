#include "Button.h"

Button::Button(sf::RenderWindow* window) : m_windowInstance(window) {
	FileManager::LoadFormFile(this->m_ButtonTexture, "asset/picture/Button.png");

	m_ButtonSprite.setTexture(this->m_ButtonTexture);
}

void Button::addButton() {
	this->m_Button.push_back(this->m_ButtonSprite);
}

void Button::setPosition(unsigned short index, sf::Vector2f position) {
	this->m_Button[index].setPosition(position);
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
	for (sf::Sprite i : m_Button)
		this->m_windowInstance->draw(i);
}
