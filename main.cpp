#include "Pasitha.h"
#define BUTTONSIZE { 259.f, 154.f }

enum Scene {
	menu, setting, credit, game, choose_character
};

struct DiscordState {
	std::unique_ptr<discord::Core> core;
};

namespace {
	volatile bool interrupted{ false };
}

unsigned short int scene = menu;
bool Pause = false;

// render function
void renderingthread(sf::RenderWindow* window) {
	window->setActive(true);

	// the rendering loop
	while (window->isOpen()) {
		window->clear(sf::Color::Black); 

		window->display();
	}
}

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

int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "JukkyJung Adventure", sf::Style::Fullscreen);
	window.setFramerateLimit(60);

	window.setActive(false);

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("sound/Main-Theme.wav"))
		return -1;

	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.setLoop(true);
	sound.play();

	sf::Thread renderThread(&renderingthread, &window);
	sf::Thread discordSDK(&discordThread);

	renderThread.launch();
	discordSDK.launch();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseMoved:
				break;
			}
		}
	}

	return 0;
}
