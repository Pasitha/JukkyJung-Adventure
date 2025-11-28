#pragma once
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
/*
#include <discord.h>

namespace
{
    struct DiscordState {
        std::unique_ptr<discord::Core> core;
    };
}

namespace JukkyJung {
    inline void initDiscord() {
        DiscordState state{};
        discord::Core* core{};
        auto response = discord::Core::Create(742258552550195321, DiscordCreateFlags_Default, &core);
        state.core.reset(core);

        if (!state.core) {
            std::cout << "Failed to instantiate discord core! (err " << static_cast<int>(response) << ")\n";
            std::exit(-1);
        }

        discord::Activity activity{};
        activity.SetDetails("Where is JukkyJung??");
        activity.SetState("Chilling");

        // activity.GetAssets().SetLargeImage("640x480");
        // activity.GetAssets().SetLargeText("JukkyJung");
        // activity.GetAssets().SetSmallImage("640x480");
        // activity.GetAssets().SetSmallText("Level 1");

        activity.SetType(discord::ActivityType::Playing);
        state.core->ActivityManager().UpdateActivity(activity, [](discord::Result result) -> void {
                std::cout << ((result == discord::Result::Ok) ? "Succeeded" : "Failed") << " updating activity!\n";
            }
        );

        do {
            state.core->RunCallbacks();
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        } while (true);
    }
}
*/
