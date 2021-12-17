enum eScene {
	menu, game, pause
};

sf::Texture createTexture(std::string path) {
	sf::Texture texture;
	texture.loadFromFile(path);

	return texture;
}

#define NEW
#ifdef NEW

sf::RenderWindow window(sf::VideoMode(1920, 1080), "JukkyJung Adventure", sf::Style::Fullscreen);

int main() {
	unsigned short int scene = game;

	sf::Image icon;
	icon.loadFromFile("picture/Jukubot_FA2.png");
	window.setIcon(1800, 1800, icon.getPixelsPtr());
	window.setFramerateLimit(60);

	sf::RectangleShape background(sf::Vector2f(1920.f, 1080.f));
	sf::Texture backgroundTexture = createTexture("picture/Jukkyjung_adventure_background1.png");

	background.setTexture(&backgroundTexture);

	pasitha::sfml::Button b_NextState("Next State", "picture/button.png", sf::Vector2f(1500.f, 880.f));

	// main loop
	while (window.isOpen()) {
		// Event loop
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
//			case sf::Event::MouseMoved:
//				if (isHover(Inventory_button)) {
//					Inventory_button.setFillColor(sf::Color(155, 155, 155, 255));
//				}
//				else {
//					Inventory_button.setFillColor(sf::Color(255, 255, 255, 255));
//				}
//
//				if (isHover(NextState_button)) {
//					NextState_button.setFillColor(sf::Color(155, 155, 155, 255));
//				}
//				else {
//					NextState_button.setFillColor(sf::Color(255, 255, 255, 255));
//				}
//				break;
//			case sf::Event::MouseButtonPressed:
//				if (isHover(Inventory_button)) {
//					std::cout << "If you want to play the full game, you can wait to follow on Github." << std::endl << "aHR0cHM6Ly9naXRodWIuY29tL1Bhc2l0aGEvSnVra3lKdW5nLUFkdmVudHVyZQ==";
//				}
//				if (isHover(NextState_button)) {
//
//					stateEvent = (rand() % 100) + 1;
//
//					state.setString("State " + std::to_string(++stateI));
//
//					backgroundTexture.loadFromFile("picture/Jukkyjung_adventure_background" + std::to_string((rand() % 2) + 1) + ".png");
//					background.setTexture(&backgroundTexture);
//				}
//				break;
			}
		}

		// display
		window.clear();

		switch (scene) {
		case menu:
			
			break;
		case game:
			window.draw(background);
			b_NextState.draw(&window);

			break;
		}

		window.display();

	}

}
#else
int main() {
	int stateI = 1;
	int stateEvent = 0;

	sf::Music music[2];
	music[0].openFromFile("sound/Mighty and Meek - Kevin MacLeod.wav");
	music[0].setVolume(20.f);
	music[0].play();
	music[0].setLoop(true);

	music[1].openFromFile("sound/March of the Mind - Kevin MacLeod.wav");
	music[1].setVolume(20.f);
	music[1].setLoop(true);

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

	auto isHover = [&window](sf::RectangleShape& button) -> bool {
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float btnPosX = button.getPosition().x;
		float btnPosY = button.getPosition().y;

		float btnxPosWidth = btnPosX + button.getLocalBounds().width;
		float btnyPosHeight = btnPosY + button.getLocalBounds().height;

		return mouseX < btnxPosWidth&& mouseX > btnPosX && mouseY < btnyPosHeight&& mouseY > btnPosY;
	};

	auto createButton = [&ReadexPro](sf::RectangleShape& button, sf::Texture& buttonTexture, sf::Text& buttonLable, sf::Vector2f position) -> void {
		button.setPosition(position);
		button.setTexture(&buttonTexture);

		buttonLable.setCharacterSize(36);
		buttonLable.setStyle(sf::Text::Bold);
		buttonLable.setFillColor(sf::Color::Black);
		buttonLable.setPosition({ button.getPosition().x + button.getGlobalBounds().width / 2.f - buttonLable.getGlobalBounds().width / 2.f, button.getPosition().y + button.getGlobalBounds().height / 2.2f - buttonLable.getGlobalBounds().height / 2.2f });
	};

	auto createTexture = [](std::string path) -> sf::Texture {
		sf::Texture texture;
		texture.loadFromFile(path);
		return texture;
	};

	// game display
	// background
	sf::RectangleShape background(sf::Vector2f(1920.f, 1080.f));
	// button
	sf::RectangleShape Inventory_button(sf::Vector2f(286.f, 154.f));
	sf::RectangleShape NextState_button(sf::Vector2f(286.f, 154.f));

	// character
	// main character
	sf::RectangleShape JukkyJung(sf::Vector2f(450.f, 450.f));
	// monster
	sf::RectangleShape monster(sf::Vector2f(318.f, 415.f));

	sf::Texture backgroundTexture = createTexture("picture/Jukkyjung_adventure_background1.png");
	sf::Texture jukkyjungTexture;
	sf::Texture monsterTexture;
	sf::Texture buttonTexture;

	background.setPosition(0.f, 0.f);
	JukkyJung.setPosition(-50.f, 430.f);
	monster.setPosition(1480.f, 460.f);

	monsterTexture.loadFromFile("picture/truefaster.png");
	// backgroundTexture.loadFromFile("picture/Jukkyjung_adventure_background1.png");
	jukkyjungTexture.loadFromFile("picture/Jukubot_FA2.png");

	buttonTexture.loadFromFile("picture/button.png");

	sf::Text nextstate("Next State", ReadexPro);
	sf::Text inventory("Inventory", ReadexPro);
	createButton(NextState_button, buttonTexture, nextstate, sf::Vector2f(1500.f, 880.f));
	createButton(Inventory_button, buttonTexture, inventory, sf::Vector2f(75.f, 880.f));

	pasitha::sfml::Button nextStateButton("Next State", "picture/button.png", sf::Vector2f(1500.f, 880.f));

	background.setTexture(&backgroundTexture);
	JukkyJung.setTexture(&jukkyjungTexture);
	monster.setTexture(&monsterTexture);

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
					std::cout << "If you want to play the full game, you can wait to follow on Github." << std::endl << "aHR0cHM6Ly9naXRodWIuY29tL1Bhc2l0aGEvSnVra3lKdW5nLUFkdmVudHVyZQ==";
				}
				if (isHover(NextState_button)) {

					stateEvent = (rand() % 100) + 1;

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

		// main character
		window.draw(JukkyJung);
		// monster
		if (stateEvent > 50) {
			window.draw(monster);
			nextstate.setString("ATTACK");
		}
		else {
			nextstate.setString("Next State");
		}

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
		// nextStateButton.draw(window);
		window.display();
	}
	return 0;
}

#endif OLD
