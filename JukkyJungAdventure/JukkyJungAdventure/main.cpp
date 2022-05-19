// STL
#include <iostream>
#include <chrono>
#include <sstream>
#include <cstdlib>
#include <functional>
#include <thread>
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
}

// sfml
namespace {
	// render function
	void render(sf::RenderWindow* window) {
		window->setActive(true);

		// the rendering loop
		while (window->isOpen()) {
			window->clear(sf::Color::Yellow);

			window->display();
		}
	}
}

int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "JukkyJung Adventure", sf::Style::Fullscreen);
	window.setFramerateLimit(60);

	window.setActive(false);

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
		}
	}

	gameThreads.at(0)->join();
	gameThreads.at(1)->join();
	return 0;
}
