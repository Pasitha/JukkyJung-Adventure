#include "Pasitha.h"

// discord
namespace {
	struct DiscordState {
		std::unique_ptr<discord::Core> core;
	};

	volatile bool interrupted{ false };
}

// discord Thread set Activities to user
void discordRPC() {
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
}

// sfml
namespace {
	

	// font
	sf::Font ReadexPro;
	// main theme song
	sf::SoundBuffer buffer;
	sf::Sound sound;

	// main menu scene
	// Sprite
	sf::Sprite jukkyjung;
	sf::Sprite gameTitle;

	// RectangleShape
	sf::RectangleShape bNewGame(BUTTONSIZE);
	sf::RectangleShape bContinue(BUTTONSIZE);
	sf::RectangleShape bSetting(BUTTONSIZE);
	sf::RectangleShape bExit(BUTTONSIZE);

	// text
	sf::Text tNewGame("New Game", ReadexPro);
	sf::Text tContinue("Continue", ReadexPro);
	sf::Text tSetting("Setting", ReadexPro);
	sf::Text tExit("Exit", ReadexPro);

	// Texture
	sf::Texture jukkyjungTexture;
	sf::Texture gameTitleTexture;
	sf::Texture buttonTexture;
}

// game variable
namespace {
	enum scene {
		menu, setting, game, character
	};

	unsigned short int scene = menu;
	bool Pause = false;
}

// render function
void render(sf::RenderWindow* window) {
	window->setActive(true);

	// the rendering loop
	while (window->isOpen()) {
		switch (scene) {
		case menu:
			window->clear(sf::Color::Yellow);

			window->draw(jukkyjung);
			window->draw(gameTitle);

			window->draw(bNewGame);
			window->draw(bContinue);
			window->draw(bSetting);
			window->draw(bExit);

			window->draw(tNewGame);
			window->draw(tContinue);
			window->draw(tSetting);
			window->draw(tExit);

			window->display();
			break;
		}
	}
}

int main() {
	sf::Image icon;
	icon.loadFromFile("picture/JukkyJung.png");
	ReadexPro.loadFromFile("font/ReadexPro.ttf");

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "JukkyJung Adventure", sf::Style::Fullscreen);

	window.setIcon(1800, 1800, icon.getPixelsPtr());
	window.setFramerateLimit(60);
	window.setActive(false);

	std::vector<std::thread*> gameThreads {
		new std::thread(discordRPC),
		new std::thread(render, &window)
	};

	// initializer vairable
	// init sound
	if (!buffer.loadFromFile("sound/Main-Theme.wav"))
		return -1;

	// main theme
	sound.setBuffer(buffer);
	sound.setLoop(true);
	sound.play();
	
	// init sprite and texture
	if (!jukkyjungTexture.loadFromFile("picture/JukkyJung.png"))
		return -1;
	if (!gameTitleTexture.loadFromFile("picture/title.png"))
		return -1;
	if (!buttonTexture.loadFromFile("picture/button.png"))
		return -1;

	// game titie
	gameTitle.setTexture(gameTitleTexture);
	gameTitle.setScale({ 1, 1 });
	// jukkyjung
	jukkyjung.setTexture(jukkyjungTexture);
	jukkyjung.setScale({ .6f, .6f });
	jukkyjung.setPosition({ 890, 0 });
	// button
	bNewGame.setTexture(&buttonTexture);
	bContinue.setTexture(&buttonTexture);
	bSetting.setTexture(&buttonTexture);
	bExit.setTexture(&buttonTexture);

	bNewGame.setPosition({ 80, 250 });
	bContinue.setPosition({ 80, 450 });
	bSetting.setPosition({ 80, 650 });
	bExit.setPosition({ 80, 850 });

	// init text
	// Button Text
	tNewGame.setStyle(sf::Text::Bold);
	tNewGame.setFillColor(sf::Color::Black);
	tNewGame.setPosition({
		bNewGame.getPosition().x + bNewGame.getGlobalBounds().width / 2.f - tNewGame.getGlobalBounds().width / 2.f,
		bNewGame.getPosition().y + bNewGame.getGlobalBounds().height / 2.2f - tNewGame.getGlobalBounds().height / 2.2f
	});
	tContinue.setStyle(sf::Text::Bold);
	tContinue.setFillColor(sf::Color::Black);
	tContinue.setPosition({
		bContinue.getPosition().x + bContinue.getGlobalBounds().width / 2.f - tContinue.getGlobalBounds().width / 2.f,
		bContinue.getPosition().y + bContinue.getGlobalBounds().height / 2.2f - tContinue.getGlobalBounds().height / 2.2f
	});
	tSetting.setStyle(sf::Text::Bold);
	tSetting.setFillColor(sf::Color::Black);
	tSetting.setPosition({
		bSetting.getPosition().x + bSetting.getGlobalBounds().width / 2.f - tSetting.getGlobalBounds().width / 2.f,
		bSetting.getPosition().y + bSetting.getGlobalBounds().height / 2.2f - tSetting.getGlobalBounds().height / 2.2f
	});
	tExit.setStyle(sf::Text::Bold);
	tExit.setFillColor(sf::Color::Black);
	tExit.setPosition({
		bExit.getPosition().x + bExit.getGlobalBounds().width / 2.f - tExit.getGlobalBounds().width / 2.f,
		bExit.getPosition().y + bExit.getGlobalBounds().height / 2.2f - tExit.getGlobalBounds().height / 2.2f
	});

	// function
	auto isHover = [&window](sf::RectangleShape& button) -> bool {
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float btnPosX = button.getPosition().x;
		float btnPosY = button.getPosition().y;

		float btnxPosWidth = btnPosX + button.getLocalBounds().width;
		float btnyPosHeight = btnPosY + button.getLocalBounds().height;

		return mouseX < btnxPosWidth&& mouseX > btnPosX && mouseY < btnyPosHeight&& mouseY > btnPosY;
	};

	// game loop
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseMoved:
				switch (scene) {
				case menu:
					bNewGame.setFillColor((isHover(bNewGame) ? sf::Color(155, 155, 155, 255) : sf::Color(255, 255, 255, 255)));
					bContinue.setFillColor((isHover(bContinue) ? sf::Color(155, 155, 155, 255) : sf::Color(255, 255, 255, 255)));
					bSetting.setFillColor((isHover(bSetting) ? sf::Color(155, 155, 155, 255) : sf::Color(255, 255, 255, 255)));
					bExit.setFillColor((isHover(bExit) ? sf::Color(155, 155, 155, 255) : sf::Color(255, 255, 255, 255)));
					break;
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (isHover(bExit)) {
					window.close();
				}
				break;
			}
		}
	}

	gameThreads.at(0)->join();
	gameThreads.at(1)->join();

	delete gameThreads.at(0);
	delete gameThreads.at(1);
	return 0;
}
