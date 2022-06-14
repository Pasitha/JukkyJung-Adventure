// STL
#include <iostream>
#include <chrono>
#include <sstream>
#include <cstdlib>
#include <functional>
#include <thread>
#include <cmath>
#include <csignal>
#include <ctime>

// Discord SDK
#include <discord.h>

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// discord
namespace {
	struct DiscordState {
		std::unique_ptr<discord::Core> core;
	};

	volatile bool interrupted{ false };

	// discord Thread set Activities to user
	auto discordRPC = []() -> void {
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

		state.core->ActivityManager().UpdateActivity(activity, [](discord::Result result) -> void {
			std::cout << ((result == discord::Result::Ok) ? "Succeeded" : "Failed") << " updating activity!\n";
		});

		std::signal(SIGINT, [](int) -> void {
			interrupted = true;
		});

		// void Uodate
		do {
			state.core->RunCallbacks();
			std::this_thread::sleep_for(std::chrono::milliseconds(16));
		} while (!interrupted);
	};
}

// sfml
namespace {
	enum eScene {
		menu, setting, walking, battle
	};
	int scene = menu;
	bool isHold = false;
	bool isPause = false;

	bool JukkyJungTurn = true;

	sf::Font ReadexPro;
	sf::Music mainThemeSong;
	sf::Texture buttonTexture;

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//                                         main menu                                           //
	/////////////////////////////////////////////////////////////////////////////////////////////////
	sf::Text tStart("START", ReadexPro);
	sf::RectangleShape button({ 259.f, 154.f });

	sf::CircleShape volumeSlider(30);
	sf::RectangleShape volume({ 550.f, 25.f });
	/////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       walking scene                                         //
	/////////////////////////////////////////////////////////////////////////////////////////////////
	sf::RectangleShape sampleMap({ 1920.f, 1080.f });
	
	sf::RectangleShape sampleTown({ 259.f, 154.f });
	sf::Text tsampleTownName("SAMPLE", ReadexPro);
	/////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//                                        battle scene                                         //
	/////////////////////////////////////////////////////////////////////////////////////////////////
	short int JukkyJungHp = 100;
	short int enemyHp = 100;
	sf::Text tJukkyJungHp("HP: " + std::to_string(JukkyJungHp), ReadexPro);
	sf::Text tEnemyHp("HP: " + std::to_string(enemyHp), ReadexPro);

	sf::RectangleShape JukkyJung({ 1800.f, 1800.f });
	sf::Texture JukkyJungTexture;

	sf::RectangleShape enemy({ 1800.f, 1800.f });

	sf::Text tAttack("ATTACK", ReadexPro);
	sf::RectangleShape attackButton({ 259.f, 154.f });
	/////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//                                         pause menu                                          //
	/////////////////////////////////////////////////////////////////////////////////////////////////
	sf::Text tResume("RESUME", ReadexPro);
	sf::Text tExit("EXIT", ReadexPro);
	sf::RectangleShape pauseMenu({ 1920.f, 1080.f });
	sf::RectangleShape resumeButton({ 259.f, 154.f });
	sf::RectangleShape exitButton({ 259.f, 154.f });
	/////////////////////////////////////////////////////////////////////////////////////////////////


	// render function
	auto render = [](sf::RenderWindow* window) -> void {
		window->setActive(true);

		// the rendering loop
		while (window->isOpen()) {
			window->clear(sf::Color(255, 185, 0, 255));

			if (scene == menu) {
				window->draw(button);
				window->draw(tStart);
				window->draw(volume);
				window->draw(volumeSlider);
			}
			else if (scene == walking) {
				window->draw(sampleMap);

				window->draw(sampleTown);
				window->draw(tsampleTownName);
				if (isPause) {
					window->draw(pauseMenu);
					window->draw(resumeButton);
					window->draw(exitButton);

					window->draw(tResume);
					window->draw(tExit);
				}
			}
			else if (scene == battle) {
				window->draw(JukkyJung);
				window->draw(enemy);
				
				window->draw(attackButton);
				window->draw(tAttack);

				window->draw(tJukkyJungHp);
				window->draw(tEnemyHp);
				if (isPause) {
					window->draw(pauseMenu);
					window->draw(resumeButton);
					window->draw(exitButton);

					window->draw(tResume);
					window->draw(tExit);
				}
			}

			window->display();
		}
	};
}

int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "JukkyJung Adventure", sf::Style::Fullscreen);
	window.setFramerateLimit(60);

	window.setActive(false);

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//                                         function                                            //
	/////////////////////////////////////////////////////////////////////////////////////////////////
	auto isHover = [&window]<class T>(T button) ->  bool {
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float btnPosX = button.getPosition().x;
		float btnPosY = button.getPosition().y;

		float btnxPosWidth = btnPosX + button.getLocalBounds().width;
		float btnyPosHeight = btnPosY + button.getLocalBounds().height;

		return mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY;
	};

	auto buttonLable = [](sf::RectangleShape button, sf::Text& buttonLable) -> void {
		buttonLable.setCharacterSize(36);
		buttonLable.setStyle(sf::Text::Bold);
		buttonLable.setFillColor(sf::Color::Black);
		buttonLable.setPosition({
			button.getPosition().x + button.getGlobalBounds().width / 2.f - buttonLable.getGlobalBounds().width / 2.f, 
			button.getPosition().y + button.getGlobalBounds().height / 2.2f - buttonLable.getGlobalBounds().height / 2.2f
		});
	};
	/////////////////////////////////////////////////////////////////////////////////////////////////



	/////////////////////////////////////////////////////////////////////////////////////////////////
	//                                        initialize	                                       //
	/////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       loading asset										   //
	/////////////////////////////////////////////////////////////////////////////////////////////////
	if (!ReadexPro.loadFromFile("font/ReadexPro.ttf"))
		return -1;

	if (!mainThemeSong.openFromFile("sound/Main-Theme.wav"))
		return -1;

	if (!buttonTexture.loadFromFile("picture/button.png"))
		return -1;

	if (!JukkyJungTexture.loadFromFile("picture/JukkyJung.png"))
		return -1;

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//                                     initialize variable							           //
	/////////////////////////////////////////////////////////////////////////////////////////////////
	mainThemeSong.setVolume(6.f);
	mainThemeSong.setLoop(true);
	mainThemeSong.play();
	// main menu
	button.setTexture(&buttonTexture);
	button.setPosition({ 500, 500 });
	buttonLable(button, tStart);
	volume.setPosition({ 500, 300 });
	volumeSlider.setPosition({ 500, 283 });

	// walking scene
	sampleMap.setFillColor(sf::Color(155, 255, 68, 155));

	sampleTown.setTexture(&buttonTexture);
	sampleTown.setPosition({ 550.f, 550.f });
	buttonLable(sampleTown, tsampleTownName);


	// battle scene
	tJukkyJungHp.setPosition({ 50.f, 600.f });
	tEnemyHp.setPosition({ 750.f, 600.f });

	attackButton.setTexture(&buttonTexture);
	attackButton.setPosition({ 250.f, 800.f });
	buttonLable(attackButton, tAttack);

	JukkyJung.setTexture(&JukkyJungTexture);
	JukkyJung.setScale({ .35f, .35f });
	JukkyJung.setPosition({ 50.f, 20.f });
	enemy.setFillColor(sf::Color(0, 168, 155));
	enemy.setScale({ .35f, .35f });
	enemy.setPosition({ 1000.f, 20.f });

	// pause menu
	pauseMenu.setFillColor(sf::Color(0, 0, 0, 155));
	resumeButton.setPosition({ 830.f, 300.f });
	exitButton.setPosition({ 830.f, 500.f });
	resumeButton.setTexture(&buttonTexture);
	exitButton.setTexture(&buttonTexture);
	buttonLable(resumeButton, tResume);
	buttonLable(exitButton, tExit);
	/////////////////////////////////////////////////////////////////////////////////////////////////



	std::vector<std::thread*> gameThreads{
		new std::thread(discordRPC),
		new std::thread(render, &window)
	};

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////
			//											menu logic							               //
			/////////////////////////////////////////////////////////////////////////////////////////////////
			if (scene == menu) {
				if (event.type == sf::Event::MouseMoved) {
					button.setFillColor(isHover(button) ? sf::Color(155, 155, 155, 255) : sf::Color(255, 255, 255, 255));
					volumeSlider.setFillColor(isHover(volumeSlider) ? sf::Color(255, 155, 155, 255) : sf::Color(215, 215, 215, 255));
				}

				if (event.type == sf::Event::MouseButtonPressed) {
					if (isHover(button)) {
						button.setFillColor(sf::Color(255, 255, 255, 255));
						scene = walking;
					}
					// volume slider
					if (isHover(volume)) {
						isHold = true;
						volumeSlider.setFillColor(sf::Color(255, 75, 68, 255));
						volumeSlider.setPosition({ std::max((float)sf::Mouse::getPosition(window).x - 35.f, 500.f), 283.f});
					}
				}
				if (event.type == sf::Event::MouseButtonReleased) {
					isHold = false;
				}
				if (isHold) {
					volumeSlider.setFillColor(sf::Color(255, 75, 68, 255));
					volumeSlider.setPosition({
						std::max(500.f, std::min((float)sf::Mouse::getPosition(window).x - 35.f, 1020.f)), 
						283.f
					});

					mainThemeSong.setVolume(std::max(0.f, std::min(((float)sf::Mouse::getPosition(window).x - 550.f) * 100.f / 550.f, 100.f)));
				}
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////
			//										    walking logic							           //
			/////////////////////////////////////////////////////////////////////////////////////////////////
			else if (scene == walking) {
				if (event.type == sf::Event::MouseMoved) {
					sampleTown.setFillColor((isHover(sampleTown)) ? sf::Color(155, 155, 155, 255) : sf::Color(255, 255, 255, 255));
					if (isPause) {
						resumeButton.setFillColor((isHover(resumeButton)) ? sf::Color(155, 155, 155, 255) : sf::Color(255, 255, 255, 255));
						exitButton.setFillColor((isHover(exitButton)) ? sf::Color(155, 155, 155, 255) : sf::Color(255, 255, 255, 255));
					}
				}
				if (event.type == sf::Event::MouseButtonPressed) {
					if (isHover(sampleMap)) {
						scene = battle;
					}
					if (isPause) {
						if (isHover(resumeButton)) {
							resumeButton.setFillColor(sf::Color(255, 255, 255, 255));
							isPause = false;
						}
						if (isHover(exitButton)) {
							exitButton.setFillColor(sf::Color(255, 255, 255, 255));
							isPause = false;
							scene = menu;
						}
					}
				}
				// pause
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Escape && !isPause) {
						isPause = true;
					}
					else if (event.key.code == sf::Keyboard::Escape && isPause) {
						isPause = false;
					}
				}
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////
			//										    battle logic							           //
			/////////////////////////////////////////////////////////////////////////////////////////////////
			else if (scene == battle) {
				if (event.type == sf::Event::MouseMoved) {
					attackButton.setFillColor((isHover(attackButton)) ? sf::Color(155, 155, 155, 255) : sf::Color(255, 255, 255, 255));
					if (isPause) {
						resumeButton.setFillColor((isHover(resumeButton)) ? sf::Color(155, 155, 155, 255) : sf::Color(255, 255, 255, 255));
						exitButton.setFillColor((isHover(exitButton)) ? sf::Color(155, 155, 155, 255) : sf::Color(255, 255, 255, 255));
					}
				}
				if (event.type == sf::Event::MouseButtonPressed) {
					if (isHover(attackButton)) {
						JukkyJungTurn = false;

						tAttack.setString("ATTACK...");
						buttonLable(attackButton, tAttack);
						
						// update enemy Hp
						int damage = 50; // (rand() % 10) + 1;

						if (enemyHp - damage <= 0) {
							tEnemyHp.setString("HP: 0");

							// JukkyJung Attack animation
							for (int i = 0; i < 50; i++) {
								JukkyJung.move({ 1, 0 });
								enemy.move({ 15 * (float)std::pow(-1, i), 0.f });
								enemy.setFillColor(sf::Color(255, 255, 255, 255 - (255 * (i * 2) / 100)));
								std::this_thread::sleep_for(std::chrono::milliseconds(3));
							}
							enemy.setPosition({ 1000.f, 20.f });
							std::this_thread::sleep_for(std::chrono::milliseconds(30));
							for (int i = 0; i < 50; i++) {
								JukkyJung.move({ -1, 0 });
								std::this_thread::sleep_for(std::chrono::milliseconds(2));
							}

							std::this_thread::sleep_for(std::chrono::milliseconds(800));

							enemy.setFillColor(sf::Color(0, 168, 155));
							enemyHp = 100;
							tEnemyHp.setString("HP: " + std::to_string(enemyHp));

							scene = walking;
						}
						else if (enemyHp - damage > 0) {
							enemyHp -= damage;
							tEnemyHp.setString("HP: " + std::to_string(enemyHp));

							// JukkyJung Attack animation
							for (int i = 0; i < 50; i++) {
								JukkyJung.move({ 1, 0 });
								enemy.move({ 15 * (float)std::pow(-1, i), 0.f });
								std::this_thread::sleep_for(std::chrono::milliseconds(3));
							}
							enemy.setPosition({ 1000.f, 20.f });
							std::this_thread::sleep_for(std::chrono::milliseconds(30));
							for (int i = 0; i < 50; i++) {
								JukkyJung.move({ -1, 0 });
								std::this_thread::sleep_for(std::chrono::milliseconds(2));
							}

							std::this_thread::sleep_for(std::chrono::milliseconds(300));

							// update JukkyJung Hp
							int enemyDamage = (rand() % 10) + 1;

							if (JukkyJungHp - enemyDamage) {
								JukkyJungHp -= enemyDamage;
								tJukkyJungHp.setString("HP: " + std::to_string(JukkyJungHp));

								// enemy Attack animation
								for (int i = 0; i < 50; i++) {
									enemy.move({ -1, 0 });
									JukkyJung.move({ 15 * (float)std::pow(-1, i), 0.f });
									std::this_thread::sleep_for(std::chrono::milliseconds(3));
								}
								JukkyJung.setPosition({ 50.f, 20.f });
								std::this_thread::sleep_for(std::chrono::milliseconds(30));
								for (int i = 0; i < 50; i++) {
									enemy.move({ 1, 0 });
									std::this_thread::sleep_for(std::chrono::milliseconds(2));
								}
							}
						}

						tAttack.setString("ATTACK");
						buttonLable(attackButton, tAttack);
					}
					if (isPause) {
						if (isHover(resumeButton)) {
							resumeButton.setFillColor(sf::Color(255, 255, 255, 255));
							isPause = false;
						}
						if (isHover(exitButton)) {
							exitButton.setFillColor(sf::Color(255, 255, 255, 255));
							isPause = false;
							scene = menu;
						}
					}
				}
				// pause
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Escape && !isPause) {
						isPause = true;
					}
					else if (event.key.code == sf::Keyboard::Escape && isPause) {
						isPause = false;
					}
				}
			}

		}
	}

	gameThreads.at(0)->join();
	gameThreads.at(1)->join();
	return 0;
}
