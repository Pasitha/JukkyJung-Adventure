// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// STL
#include <iostream>
#include <chrono>
#include <thread>

#include "Pasitha.h"

enum eScene {
	menu, setting, credit, game, choose_character
};

// Function used to create sf::Texture
sf::Texture createTexture(std::string path) {
	sf::Texture texture;
	if (!texture.loadFromFile(path))
		std::cerr << "Can't loadFile at: " << path << "\n";
	return texture;
}

// Function used to initializer sf::Text to Bold
void createTextBold(sf::Text& text, std::string lable, int size, sf::Vector2f position, sf::Font& font, sf::Color color = sf::Color(155, 155, 155, 255), float OutlineThickness = 3.5f) {
	text.setString(lable);
	text.setFont(font);
	text.setCharacterSize(size);
	text.setPosition(position);
	text.setFillColor(color);
	text.setOutlineThickness(OutlineThickness);
	text.setStyle(sf::Text::Bold);
};

// Function used to initializer sf::Rectangle
void createRectangleTexture(sf::RectangleShape& rectangle, sf::Texture& texture, sf::Vector2f position = { 0, 0 }) {
	rectangle.setTexture(&texture);
	rectangle.setPosition(position);
}

void createRectangleTexture(sf::RectangleShape& rectangle, std::string path, sf::Vector2f position = { 0, 0 }) {
	sf::Texture texture = createTexture(path);
	rectangle.setTexture(&texture);
	rectangle.setPosition(position);
}

void createButton(sf::RectangleShape& button, sf::Texture& buttonTexture, sf::Text& buttonLable, sf::Vector2f position, sf::Color TextColor = sf::Color::Black) {
	button.setPosition(position);
	button.setTexture(&buttonTexture);

	buttonLable.setCharacterSize(36);
	buttonLable.setStyle(sf::Text::Bold);
	buttonLable.setFillColor(TextColor);
	buttonLable.setPosition({ button.getPosition().x + button.getGlobalBounds().width / 2.f - buttonLable.getGlobalBounds().width / 2.f, button.getPosition().y + button.getGlobalBounds().height / 2.2f - buttonLable.getGlobalBounds().height / 2.2f });
};

int main() {
	unsigned short int scene = menu;
	bool Pause = false;

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "JukkyJung Adventure", sf::Style::Fullscreen);
	sf::Music music[2];
	sf::Image icon;

	sf::Font ReadexPro;

	// Function used to check mouse is hover the sf::Rectangle
	auto isHover = [&window](sf::RectangleShape& button) -> bool {
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float btnPosX = button.getPosition().x;
		float btnPosY = button.getPosition().y;

		float btnxPosWidth = btnPosX + button.getLocalBounds().width;
		float btnyPosHeight = btnPosY + button.getLocalBounds().height;

		return mouseX < btnxPosWidth&& mouseX > btnPosX && mouseY < btnyPosHeight&& mouseY > btnPosY;
	};

	// initializer vairable
	// RectangleShape
	sf::RectangleShape background({ 1920.f, 1080.f });
	sf::RectangleShape fade({ 300.f, 1080.f });
	sf::RectangleShape BigBlackBox({ 1920.f, 1080.f });
	
	// Texture
	sf::Texture backgroundTexture = createTexture("picture/Jukkyjung_adventure_background1.png");
	sf::Texture JukkyJung = createTexture("picture/JukkyJung.png");
	sf::Texture border = createTexture("picture/border.png");
	sf::Texture button = createTexture("picture/button.png");
	sf::Texture fadeTexture = createTexture("picture/fade.png");

	BigBlackBox.setFillColor(sf::Color(0, 0, 0, 255));
	BigBlackBox.setPosition({ 300.f, 0.f });
	fade.setTexture(&fadeTexture);

	// sound
	music[0].openFromFile("sound/Mighty and Meek - Kevin MacLeod.wav");
	music[0].setVolume(18.f);
	music[0].play();
	music[0].setLoop(true);

	music[1].openFromFile("sound/March of the Mind - Kevin MacLeod.wav");
	music[1].setVolume(18.f);
	music[1].setLoop(true);

	// font
	ReadexPro.loadFromFile("font/ReadexPro.ttf");

	icon.loadFromFile("picture/JukkyJung.png");
	window.setIcon(1800, 1800, icon.getPixelsPtr());
	window.setFramerateLimit(60);
	// end initializer vairable section

	// initializer game scene
	// menu game
	sf::RectangleShape GameTitle({ 1080, 720 });
	sf::RectangleShape picJukkyJung({ 900, 900 });

	sf::RectangleShape b_Start({ 289.f, 154.f });
	sf::RectangleShape b_Setting({ 289.f, 154.f });
	sf::RectangleShape b_ExitGame({ 289.f, 154.f });

	sf::Texture GameTitleTexture = createTexture("picture/title.png");
	sf::Text t_Start("START", ReadexPro);
	sf::Text t_Setting("SETTING", ReadexPro);
	sf::Text t_ExitGame("EXIT", ReadexPro);
	
	createRectangleTexture(picJukkyJung, JukkyJung, { 1000, 200 });
	createRectangleTexture(GameTitle, GameTitleTexture, { 0, 0 });
	createButton(b_Start, button, t_Start, { 50, 250 });
	createButton(b_Setting, button, t_Setting, { 50, 550 });
	createButton(b_ExitGame, button, t_ExitGame, { 50, 850 });

	// pause menu
	sf::RectangleShape PauseBackground({ 1920, 1080 });
	sf::RectangleShape b_Resume({ 289.f, 154.f });
	sf::RectangleShape b_Exit({ 289.f, 154.f });
	sf::Text t_Resume("RESUME", ReadexPro);
	sf::Text t_Exit("EXIT", ReadexPro);

	PauseBackground.setFillColor(sf::Color(0, 0, 0, 200));
	createButton(b_Resume, button, t_Resume, { 800, 300 });
	createButton(b_Exit, button, t_Exit, { 800, 500 });
	
	// game
	background.setTexture(&backgroundTexture);

	sf::RectangleShape guiBar({ 1820.f, 180.f });
	sf::RectangleShape guiPlayerStats({ 500.f, 180.f });
	sf::RectangleShape guiMonsterStats({ 500.f, 180.f });
	sf::RectangleShape mainCharacter({ 450.f, 450.f });

	sf::RectangleShape b_ChooseCharacter({ 289.f, 154.f });

	sf::Text t_PlayerHP;
	sf::Text t_PlayerDEF;
	sf::Text t_PlayerATK;
	sf::Text t_MonsterHP;  
	sf::Text t_MonsterDEF;
	sf::Text t_MonsterATK;
	sf::Text t_ChooseCharacter("Character", ReadexPro);
		
	createRectangleTexture(guiBar, border, { 50, 860 });
	createRectangleTexture(guiPlayerStats, border, { 50, 860 });
	createRectangleTexture(guiMonsterStats, border, { 1370, 860 });
	createRectangleTexture(mainCharacter, JukkyJung, { 70, 410 });

	createTextBold(t_PlayerHP, "HP: 500", 32, { 60.f, 870.f }, ReadexPro);
	createTextBold(t_PlayerDEF, "DEF: 100", 32, { 60.f, 910.f }, ReadexPro);
	createTextBold(t_PlayerATK, "ATK: 100", 32, { 60.f, 950.f }, ReadexPro);
	createTextBold(t_MonsterHP, "HP: 100", 32, { 1380.f, 870.f }, ReadexPro);
	createTextBold(t_MonsterDEF, "DEF: 10", 32, { 1380.f, 910.f }, ReadexPro);
	createTextBold(t_MonsterATK, "ATK: 10", 32, { 1380.f, 950.f }, ReadexPro);

	createButton(b_ChooseCharacter, button, t_ChooseCharacter, { 800.f, 880.f });

	// choose_character
	sf::RectangleShape box_MainCharacter({ 450, 450 });
	sf::RectangleShape box_Character1({ 450, 450 });
	sf::RectangleShape box_Character2({ 450, 450 });
	sf::RectangleShape characterJukkyJung({ 450, 450 });

	sf::RectangleShape b_BackToGame({ 289.f, 154.f });
	sf::Text t_BackToGame("EXIT", ReadexPro);

	box_MainCharacter.setFillColor(sf::Color::White);
	box_Character1.setFillColor(sf::Color::White);
	box_Character2.setFillColor(sf::Color::White);

	box_MainCharacter.setPosition({ 100, 100 });
	box_Character1.setPosition({ 600, 100 });
	box_Character2.setPosition({ 1100, 100 });

	createButton(b_BackToGame, button, t_BackToGame, { 45, 900 });
	createRectangleTexture(characterJukkyJung, JukkyJung, { 600, 100 });

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
				switch (scene) {
				case menu:
					// game menu
					b_Start.setFillColor(isHover(b_Start) ? sf::Color(155, 155, 155, 255) : sf::Color(255, 255, 255, 255));
					b_Setting.setFillColor(isHover(b_Setting) ? sf::Color(155, 155, 155, 255) : sf::Color(255, 255, 255, 255));
					b_ExitGame.setFillColor(isHover(b_ExitGame) ? sf::Color(155, 155, 155, 255) : sf::Color(255, 255, 255, 255));

					break;
				case game:
					// choose character
					b_ChooseCharacter.setFillColor(isHover(b_ChooseCharacter) ? sf::Color(155, 155, 155, 255) : sf::Color(255, 255, 255, 255));
					
					// pause menu
					if (Pause) {
						b_Resume.setFillColor(isHover(b_Resume) ? sf::Color(155, 155, 155, 255) : sf::Color(255, 255, 255, 255));
						
						b_Exit.setFillColor(isHover(b_Exit) ? sf::Color(155, 155, 155, 255) : sf::Color(255, 255, 255, 255));
					}
					break;
				case choose_character:
					b_BackToGame.setFillColor(isHover(b_BackToGame) ? sf::Color(155, 155, 155, 255) : sf::Color(255, 255, 255, 255));

					break;
				}
				break;
			case sf::Event::MouseButtonPressed:
				switch (scene) {
				case menu:
					if (isHover(b_Start)) {
						scene = game;
					}
					else if (isHover(b_Setting)) {
						scene = setting;
					}
					else if (isHover(b_ExitGame)) {
						for (int i = 0; i < 200; i++) {
							window.clear(sf::Color(255, 170, 0, 155));
							fade.move({ 10.f, 0.0f });
							BigBlackBox.move({ 10.f, 0.0f });

							window.draw(BigBlackBox);
							window.draw(fade);

							std::this_thread::sleep_for(std::chrono::milliseconds(10));
							window.display();
						}

						fade.setPosition({ .0f, .0f });
						BigBlackBox.setPosition({ 300.0f, .0f });
						window.close();
					}
					break;
				case game:
					if (isHover(b_ChooseCharacter)) {
						for (int i = 0; i < 50; i++) {
							window.clear(sf::Color(255, 170, 0, 155));
							fade.move({ 35.f, 0.0f });
							BigBlackBox.move({ 35.f, 0.0f });

							window.draw(box_MainCharacter);
							window.draw(box_Character1);
							window.draw(box_Character2);

							window.draw(characterJukkyJung);

							window.draw(b_BackToGame);
							window.draw(t_BackToGame);


							window.draw(BigBlackBox);
							window.draw(fade);

							std::this_thread::sleep_for(std::chrono::milliseconds(10));
							window.display();
						}

						fade.setPosition({ .0f, .0f });
						BigBlackBox.setPosition({ 300.0f, .0f });
						scene = choose_character;
					}
					if (Pause) {
						if (isHover(b_Resume)) {
							Pause = false;

							b_Resume.setFillColor(sf::Color(255, 255, 255, 255));
						}
						if (isHover(b_Exit)) {
							scene = menu;
							Pause = false;

							b_Exit.setFillColor(sf::Color(255, 255, 255, 255));
						}
					}
					break;
				case choose_character:
					if (isHover(b_BackToGame)) {
						scene = game;
					}
					break;
				}
				break;
			}
		}

		// display
		window.clear(sf::Color(255, 170, 0, 155));

		switch (scene) {
		case menu:
			window.draw(GameTitle);
			window.draw(picJukkyJung);

			window.draw(b_Start);
			window.draw(t_Start);
			window.draw(b_Setting);
			window.draw(t_Setting);
			window.draw(b_ExitGame);
			window.draw(t_ExitGame);

			break;
		case setting:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				scene = menu;
			}
			window.draw(picJukkyJung);
			break;
		case game:
			window.draw(background);
			window.draw(guiBar);
			window.draw(guiPlayerStats);
			window.draw(guiMonsterStats);

			window.draw(mainCharacter);
			window.draw(t_PlayerHP);

			window.draw(t_PlayerDEF);
			window.draw(t_PlayerATK);

			window.draw(t_MonsterHP);
			window.draw(t_MonsterDEF);
			window.draw(t_MonsterATK);

			window.draw(b_ChooseCharacter);
			window.draw(t_ChooseCharacter);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !Pause && event.KeyReleased) {

				Pause = true;
				std::cout << "Escape press from game" << std::endl;
			}
			if (Pause) {
				window.draw(PauseBackground);
				window.draw(b_Resume);
				window.draw(b_Exit);
				window.draw(t_Resume);
				window.draw(t_Exit);
			}
			break;
		case choose_character:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				scene = game;

			window.draw(box_MainCharacter);
			window.draw(box_Character1);
			window.draw(box_Character2);

			window.draw(characterJukkyJung);

			window.draw(b_BackToGame);
			window.draw(t_BackToGame);
			break;
		}

		window.display();
	}

	return 0;
}
