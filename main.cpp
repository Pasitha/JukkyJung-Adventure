#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <chrono>
#include <cstdlib>
#include <functional>

int main() {
	int stateI = 1;

	sf::Music music;
	music.openFromFile("sound/Mighty and Meek - Kevin MacLeod.wav");
	music.setVolume(20.f);
	music.play();
	music.setLoop(true);

	sf::Font ReadexPro;
	ReadexPro.loadFromFile("font/ReadexPro.ttf");

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "JukkyJung Adventure", sf::Style::Fullscreen);

	sf::Image icon;
	icon.loadFromFile("picture/Jukubot_FA2.png");
	window.setIcon(1800, 1800, icon.getPixelsPtr());
	window.setFramerateLimit(60);

	auto setTextBold = [&window](sf::Text& text, int size, sf::Vector2f position, sf::Color color = sf::Color(155, 155, 155, 255), float OutlineThickness = 3.5f) -> void {
		text.setCharacterSize(size);
		text.setPosition(position);
		text.setFillColor(color);
		text.setOutlineThickness(OutlineThickness);
		text.setStyle(sf::Text::Bold);
	};

	auto isHover = [&window](sf::RectangleShape button) -> bool {
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float btnPosX = button.getPosition().x;
		float btnPosY = button.getPosition().y;

		float btnxPosWidth = btnPosX + button.getLocalBounds().width;
		float btnyPosHeight = btnPosY + button.getLocalBounds().height;
		
		return mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY;
	};

	auto createButton = [&ReadexPro](sf::RectangleShape &button, sf::Texture &buttonTexture, sf::Text &buttonLable, sf::Vector2f position) -> void {
		button.setPosition(position);
		button.setTexture(&buttonTexture);

		buttonLable.setCharacterSize(36);
		buttonLable.setStyle(sf::Text::Bold);
		buttonLable.setFillColor(sf::Color::Black);
		buttonLable.setPosition({ button.getPosition().x + button.getGlobalBounds().width / 2.f - buttonLable.getGlobalBounds().width / 2.f, button.getPosition().y + button.getGlobalBounds().height / 2.2f - buttonLable.getGlobalBounds().height / 2.2f });
	};

	// game display
	sf::RectangleShape background(sf::Vector2f(1920.f, 1080.f));
	sf::RectangleShape JukkyJung(sf::Vector2f(450.f, 450.f));
	sf::RectangleShape statusBar(sf::Vector2f(310, 36));

	// button
	sf::RectangleShape Inventory_button(sf::Vector2f(286.f, 154.f));
	sf::RectangleShape NextState_button(sf::Vector2f(286.f, 154.f));

	sf::Texture backgroundTexture;
	sf::Texture jukkyjungTexture;
	sf::Texture statusBarTexture;
	sf::Texture hpBarTexture;
	sf::Texture buttonTexture;

	background.setPosition(0.f, 0.f);
	JukkyJung.setPosition(-50.f, 430.f);
	statusBar.setPosition(1540.f, 50.f);
	
	backgroundTexture.loadFromFile("picture/Jukkyjung_adventure_background1.png");
	jukkyjungTexture.loadFromFile("picture/Jukubot_FA2.png");
	statusBarTexture.loadFromFile("picture/statusBar.png");
	hpBarTexture.loadFromFile("picture/hpBar.png");
	buttonTexture.loadFromFile("picture/button.png");

	sf::Text nextstate("Next State", ReadexPro);
	sf::Text inventory("Inventory", ReadexPro);
	createButton(NextState_button, buttonTexture, nextstate, sf::Vector2f(1500.f, 880.f));
	createButton(Inventory_button, buttonTexture, inventory, sf::Vector2f(75.f, 880.f));

	background.setTexture(&backgroundTexture);
	JukkyJung.setTexture(&jukkyjungTexture);
	statusBar.setTexture(&statusBarTexture);
	
	sf::Text state("STATE 1", ReadexPro);
	sf::Text Hp("HP: 10", ReadexPro);
	sf::Text Atk("ATK: 1", ReadexPro);
	sf::Text Defence("DEF: 1", ReadexPro);
		
	setTextBold(state, 48, sf::Vector2f(48, 50));
	setTextBold(Hp, 36, sf::Vector2f(1750.f, 50.f));
	setTextBold(Atk, 36, sf::Vector2f(1750.f, 85.f));
	setTextBold(Defence, 36, sf::Vector2f(1750.f, 125.f));

	// main loop
	while (window.isOpen()) {
		// Event loop
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseMoved:
				if (isHover(Inventory_button)) {
					Inventory_button.setFillColor(sf::Color(155, 155, 155, 255));
				}
				else {
					Inventory_button.setFillColor(sf::Color(255, 255, 255, 255));
				}

				if (isHover(NextState_button)) {
					NextState_button.setFillColor(sf::Color(155, 155, 155, 255));
				}
				else {
					NextState_button.setFillColor(sf::Color(255, 255, 255, 255));
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (isHover(Inventory_button)) {
					std::cout << "You clicked!" << std::endl;
				}
				if (isHover(NextState_button)) {
					state.setString("State " + std::to_string(++stateI));

					backgroundTexture.loadFromFile("picture/Jukkyjung_adventure_background" + std::to_string((rand() % 2) + 1) + ".png");
					background.setTexture(&backgroundTexture);
				}
				break;
			}
		}
		
		window.clear();
		// picture
		window.draw(background);
		window.draw(JukkyJung);

		// dispolay text
		window.draw(state);
		window.draw(Hp);
		window.draw(Atk);
		window.draw(Defence);
		
		window.draw(Inventory_button);
		window.draw(inventory);
		
		// button
		window.draw(NextState_button);
		window.draw(nextstate);
		window.display();
	}

	return 0;
}
