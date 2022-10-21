#pragma once
#include "common.h"

struct DiscordState {
	std::unique_ptr<discord::Core> core;
};

namespace {
	volatile bool interrupted{ false };
}

auto updateDiscordRPC = []() -> void {
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

	do {
		state.core->RunCallbacks();
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	} while (!interrupted);
};
