#include "common.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(600, 200), "SFML works!");
	window.setActive(false);

	std::vector<std::thread*> gameThreads {
		new std::thread(updateDiscordRPC),
		new std::thread(render, &window)
	};

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				interrupted = false;
				window.close();
			}
		}
	}

	gameThreads.at(0)->join();
	gameThreads.at(1)->join();

	return 0;
}