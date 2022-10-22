#include "common.h"

int main() {
	sf::RenderWindow window(
		sf::VideoMode(1920, 1080),
		"SFML works!",
		sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close
	);
	window.setActive(false);

	std::vector<std::thread*> gameThreads {
		new std::thread(updateDiscordRPC),
		new std::thread(render, &window)
	};

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				std::raise(SIGINT);
				window.close();
			}
		}
	}

	gameThreads.at(0)->join();
	gameThreads.at(1)->join();
	
	for (auto gameThread : gameThreads)
		delete gameThread;
	gameThreads.clear();
	return 0;
}
