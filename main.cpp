#include "Pasitha.h"

#define BUTTONSIZE { 259.f, 154.f }

enum eScene {
	menu, setting, credit, game, choose_character
};

struct DiscordState {
	std::unique_ptr<discord::Core> core;
};

namespace {
	volatile bool interrupted{ false };
}

#define UPDATE
#ifdef UPDATE

// Discord Thread set Activities to user
void discordThread() {
	DiscordState state{};

	discord::Core* core{};
	auto response = discord::Core::Create(742258552550195321, DiscordCreateFlags_Default, &core);

	state.core.reset(core);

	if (!state.core) {
		std::cout << "Failed to instantiate Discord!";
		std::exit(-1);
	}

	discord::Activity activity{};
	activity.SetDetails("Where is JukkyJung??");
	activity.SetState("Let's Help JukkyJung!!");
	activity.GetAssets().SetSmallImage("jukucrush");
	activity.GetAssets().SetSmallText("Jukucrush game");
	activity.GetAssets().SetLargeImage("jukubot");
	activity.GetAssets().SetLargeText("JukkyJung Adventure");
	activity.GetTimestamps().SetStart(time(0));
	activity.SetType(discord::ActivityType::Playing);

	state.core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
		std::cout << ((result == discord::Result::Ok) ? "Succeeded" : "Failed") << " updating activity!\n";
	});

	std::signal(SIGINT, [](int) {
		interrupted = true;
	});

	// void Update()
	do {
		state.core->RunCallbacks();
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	} while (!interrupted);
}

// render function
void renderingthread(sf::RenderWindow* window) {
	window->setActive(true);

	// the rendering loop
	while (window->isOpen()) {
		window->clear(sf::Color::Black); 

		window->display();
	}
}

int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "JukkyJung Adventure", sf::Style::Fullscreen);
	window.setFramerateLimit(60);

	window.setActive(false);

	sf::Thread renderThread(&renderingthread, &window);
	sf::Thread discordSDK(&discordThread);

	renderThread.launch();
	discordSDK.launch();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::MouseMoved:
				std::cout << "Mouse Moved\n";
				break;
			}

		}
	}

	return 0;
}
#else
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
	std::vector<std::thread*> threads;

	// Discord SDK thread
	threads.push_back(new std::thread([&]() -> void {
		DiscordState state{};

		discord::Core* core{};
		auto response = discord::Core::Create(742258552550195321, DiscordCreateFlags_Default, &core);

		state.core.reset(core);

		if (!state.core) {
			std::cout << "Failed to instantiate Discord!";
			std::exit(-1);
		}

		discord::Activity activity{};
		activity.SetDetails("Where is JukkyJung??");
		activity.SetState("Let's Help JukkyJung!!");
		activity.GetAssets().SetSmallImage("jukucrush");
		activity.GetAssets().SetSmallText("Jukucrush game");
		activity.GetAssets().SetLargeImage("jukubot");
		activity.GetAssets().SetLargeText("JukkyJung Adventure");
		activity.GetTimestamps().SetStart(time(0));
		activity.SetType(discord::ActivityType::Playing);

		state.core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
			std::cout << ((result == discord::Result::Ok) ? "Succeeded" : "Failed") << " updating activity!\n";
		});

		std::signal(SIGINT, [](int) {
			interrupted = true;
		});

		// void Uodate
		do {
			state.core->RunCallbacks();
			std::this_thread::sleep_for(std::chrono::milliseconds(16));
		} while (!interrupted);
	}));

	// sfml thread
	threads.push_back(new std::thread([&]() -> void {
		unsigned short int scene = menu;
		bool Pause = false;

		// set pasitha default font
		pasitha::sfml::ReadexPro.loadFromFile("font/ReadexPro.ttf");

		sf::Image icon;
		icon.loadFromFile("picture/JukkyJung.png");

		sf::RenderWindow window(sf::VideoMode(1920, 1080), "JukkyJung Adventure", sf::Style::Fullscreen);
		window.setIcon(1800, 1800, icon.getPixelsPtr());
		window.setFramerateLimit(60);

		// sound
		sf::Music music[2];
		music[0].openFromFile("sound/Mighty and Meek - Kevin MacLeod.wav");
		music[0].setVolume(18.f);
		music[0].play();
		music[0].setLoop(true);

		music[1].openFromFile("sound/March of the Mind - Kevin MacLeod.wav");
		music[1].setVolume(18.f);
		music[1].setLoop(true);

		// font
		sf::Font ReadexPro;
		ReadexPro.loadFromFile("font/ReadexPro.ttf");

		// Function used to check mouse is hover the sf::Rectangle
		auto isHover = [&window](sf::RectangleShape& button) -> bool {
			float mouseX = sf::Mouse::getPosition(window).x;
			float mouseY = sf::Mouse::getPosition(window).y;

			float btnPosX = button.getPosition().x;
			float btnPosY = button.getPosition().y;

			float btnxPosWidth = btnPosX + button.getLocalBounds().width;
			float btnyPosHeight = btnPosY + button.getLocalBounds().height;

			return mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY;
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
		// end initializer vairable section

		// initializer game scene
		// menu game
		sf::Texture GameTitleTexture = createTexture("picture/title.png");

		sf::RectangleShape GameTitle({ 1080, 720 });
		sf::RectangleShape picJukkyJung({ 900, 900 });
		createRectangleTexture(picJukkyJung, JukkyJung, { 1000, 200 });
		createRectangleTexture(GameTitle, GameTitleTexture, { 0, 0 });

		pasitha::sfml::Button bStart("START", BUTTONSIZE, button, 36, { 50, 250 });
		pasitha::sfml::Button bSetting("SETTING", BUTTONSIZE, button, 36, { 50, 550 });
		pasitha::sfml::Button bExit("EXIT", BUTTONSIZE, button, 36, { 50, 850 });	
		
		// pause menu
		sf::RectangleShape PauseBackground({ 1920, 1080 });
		PauseBackground.setFillColor(sf::Color(0, 0, 0, 200));

		pasitha::sfml::Button bPauseResume("RESUME", BUTTONSIZE, button, 36, { 800, 300 });
		pasitha::sfml::Button bPauseExit("EXIT", BUTTONSIZE, button, 36, { 800, 500 });
		
		// game
		background.setTexture(&backgroundTexture);

		sf::RectangleShape guiBar({ 1820.f, 180.f });
		sf::RectangleShape guiPlayerStats({ 500.f, 180.f });
		sf::RectangleShape guiMonsterStats({ 500.f, 180.f });
		sf::RectangleShape mainCharacter({ 450.f, 450.f });

		pasitha::sfml::Button bChooseCharacter("Character", BUTTONSIZE, button, 36, { 800.f, 880.f });

		sf::Text t_PlayerHP;
		sf::Text t_PlayerDEF;
		sf::Text t_PlayerATK;
		sf::Text t_MonsterHP;  
		sf::Text t_MonsterDEF;
		sf::Text t_MonsterATK;
			
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

		// choose_character
		sf::RectangleShape box_MainCharacter({ 450, 450 });
		sf::RectangleShape box_Character1({ 450, 450 });
		sf::RectangleShape box_Character2({ 450, 450 });
		sf::RectangleShape characterJukkyJung({ 450, 450 });

		pasitha::sfml::Button bbackToGame("EXIT", BUTTONSIZE, button, 36, { 45, 900 });

		box_MainCharacter.setFillColor(sf::Color::White);
		box_Character1.setFillColor(sf::Color::White);
		box_Character2.setFillColor(sf::Color::White);

		box_MainCharacter.setPosition({ 100, 100 });
		box_Character1.setPosition({ 600, 100 });
		box_Character2.setPosition({ 1100, 100 });

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
						bStart.setFillColor(bStart.isHover(window) ? sf::Color(155, 155, 155, 255) : sf::Color(255, 255, 255, 255));
						bSetting.setFillColor(bSetting.isHover(window) ? sf::Color(155, 155, 155, 255) : sf::Color(255, 255, 255, 255));
						bExit.setFillColor(bExit.isHover(window) ? sf::Color(155, 155, 155, 255) : sf::Color(255, 255, 255, 255));

						break;
					case game:
						// choose character
						bChooseCharacter.setFillColor(bChooseCharacter.isHover(window) ? sf::Color(155, 155, 155, 255) : sf::Color(255, 255, 255, 255));
						
						// pause menu
						if (Pause) {
							bPauseResume.setFillColor(bPauseResume.isHover(window) ? sf::Color(155, 155, 155, 255) : sf::Color(255, 255, 255, 255));
							bPauseExit.setFillColor(bPauseExit.isHover(window) ? sf::Color(155, 155, 155, 255) : sf::Color(255, 255, 255, 255));
						}
						break;
					case choose_character:
						bbackToGame.setFillColor(bbackToGame.isHover(window) ? sf::Color(155, 155, 155, 255) : sf::Color(255, 255, 255, 255));

						break;
					}
					break;
				case sf::Event::MouseButtonPressed:
					switch (scene) {
					case menu:
						if (bStart.isHover(window)) {
							scene = game;
							bStart.setFillColor(sf::Color(255, 255, 255, 255));
						}
						else if (bSetting.isHover(window)) {
							scene = setting;
							bSetting.setFillColor(sf::Color(255, 255, 255, 255));
						}
						else if (bExit.isHover(window)) {
							bExit.setFillColor(sf::Color(255, 255, 255, 255));
							for (int i = 0; i < 200; i++) {
								window.clear(sf::Color(255, 170, 0, 155));

								window.draw(GameTitle);
								window.draw(picJukkyJung);

								bStart.draw(window);
								bSetting.draw(window);
								bExit.draw(window);

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
						if (bChooseCharacter.isHover(window)) {
							for (int i = 0; i < 50; i++) {
								window.clear(sf::Color(255, 170, 0, 155));

								fade.move({ 37.f, 0.0f });
								BigBlackBox.move({ 37.f, 0.0f });

								window.draw(box_MainCharacter);
								window.draw(box_Character1);
								window.draw(box_Character2);

								window.draw(characterJukkyJung);

								bbackToGame.draw(window);

								window.draw(BigBlackBox);
								window.draw(fade);

								window.display();
								std::this_thread::sleep_for(std::chrono::milliseconds(10));
							}

							fade.setPosition({ .0f, .0f });
							BigBlackBox.setPosition({ 300.0f, .0f });
							scene = choose_character;
						}
						if (Pause) {
							if (bPauseResume.isHover(window)) {
								Pause = false;

								bPauseResume.setFillColor(sf::Color(255, 255, 255, 255));
							}
							if (bPauseExit.isHover(window)) {
								scene = menu;
								Pause = false;

								bPauseExit.setFillColor(sf::Color(255, 255, 255, 255));
							}
						}
						break;
					case choose_character:
						if (bbackToGame.isHover(window)) {
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

				bStart.draw(window);
				bSetting.draw(window);
				bExit.draw(window);
			
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

				bChooseCharacter.draw(window);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !Pause && event.KeyReleased) {

					Pause = true;
					std::cout << "Escape press from game" << std::endl;
				}
				if (Pause) {
					window.draw(PauseBackground);
					bPauseResume.draw(window);
					bPauseExit.draw(window);
				}
				break;
			case choose_character:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					scene = game;

				window.draw(box_MainCharacter);
				window.draw(box_Character1);
				window.draw(box_Character2);

				window.draw(characterJukkyJung);

				bbackToGame.draw(window);
				break;
			}

			window.display();
		}
		interrupted = true;
	}));

	threads.at(0)->join();
	threads.at(1)->join();

	delete threads.at(0);
	delete threads.at(1);
	return 0;
}
#endif
