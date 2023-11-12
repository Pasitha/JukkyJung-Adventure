#include "JukkyJung.h"

const float JukkyJung::JUKKYJUNG_SCALE = 0.3f;
const sf::Vector2f JukkyJung::JUKKYJUNG_POSITION = { 30, 30 };

JukkyJung::JukkyJung(sf::RenderWindow* window) : m_windowInstance(window), m_JukkyJungHealth(100) {
	FileManager::LoadFromFile(this->m_TextFont, "asset/font/ReadexPro.ttf");
	FileManager::LoadFromFile(this->m_JukkyJungTexture, "asset/picture/JukkyJung.png");
	
	m_JukkyJungHp.setFillColor(sf::Color(255, 255, 255));
	m_JukkyJungHp.setFont(this->m_TextFont);
	m_JukkyJungHp.setString("HP: 100");

	this->m_JukkyJungSprite.setTexture(this->m_JukkyJungTexture);
	this->m_JukkyJungSprite.setScale({ this->JUKKYJUNG_SCALE, this->JUKKYJUNG_SCALE });
	this->m_JukkyJungSprite.setPosition(this->JUKKYJUNG_POSITION);
}

// Destructor implementation only in debug mode
#ifdef _DEBUG
JukkyJung::~JukkyJung(){
	std::cout << "JukkyJung was destroy!" << std::endl;
}
#endif

// Shake animation method has a thread problem
// try to animate without sleep main thread
void JukkyJung::ShakeAnimation() {
	// Launch a separate thread for the shake animation
    std::thread animationThread([this]() {
        for (int i = 0; i < 10; i++) {
            this->m_JukkyJungSprite.move({ 2 - (float)std::pow(-1, i) * 4, 0 });

            // Draw in the separate thread
            this->m_windowInstance->clear();
            this->m_windowInstance->draw(this->m_JukkyJungSprite);
            this->m_windowInstance->display();

            // Sleep for a short duration to control the animation speed
            std::this_thread::sleep_for(std::chrono::milliseconds(45));
        }

        // Draw the final position
        this->m_JukkyJungSprite.setPosition(this->JUKKYJUNG_POSITION);
        this->m_windowInstance->draw(this->m_JukkyJungSprite);
        this->m_windowInstance->display();
    });

    // Wait for the thread to finish (optional)
    animationThread.join();
}

void JukkyJung::Update() {
	this->m_windowInstance->draw(this->m_JukkyJungHp);
	this->m_windowInstance->draw(this->m_JukkyJungSprite);
}
