#include "JukkyJung.h"

JukkyJung::JukkyJung(sf::RenderWindow* window) {
	this->m_windowInstance = window;

	this->m_JukkyJungTexture.loadFromFile("asset/picture/JukkyJung.png");
	this->m_JukkyJungSprite.setTexture(&this->m_JukkyJungSprite);
}

void JukkyJung::Update() {

}
