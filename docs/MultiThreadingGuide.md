# Multi-threading Guide for JukkyJung-Adventure

This guide explains how to integrate multi-threading into the JukkyJung-Adventure game for performance gains. We will focus on the most common use case for multi-threading in a game: **asynchronous asset loading**.

## Why Use Multi-threading?

In a game, it's crucial to keep the main game loop running smoothly. If the main loop is blocked for too long, the game will appear to freeze or stutter. Asset loading, especially for large assets like textures and sounds, can be a time-consuming operation that can block the main loop.

By using a separate thread to load assets, we can keep the main game loop running while the assets are being loaded in the background. This will result in a much smoother and more responsive experience for the player.

## How to Implement Asynchronous Asset Loading

We will use `std::thread` and `std::future` from the C++ standard library to implement asynchronous asset loading. `std::thread` will be used to run the asset loading code in a separate thread, and `std::future` will be used to get the result of the loading operation when it's complete.

### 1. The `FileManager`

The `FileManager` class in this project is already set up to support asynchronous loading with the `LoadAsync` method. Here's how it works:

```cpp
// In FileManager.h
template <typename T>
static std::future<bool> LoadAsync(const std::string& fileName);
```

This method returns a `std::future<bool>`, which will eventually hold the result of the loading operation ( `true` for success, `false` for failure).

### 2. Using `LoadAsync` in a Scene

Here's an example of how you could use `LoadAsync` to load a texture in a scene:

```cpp
// In any Scene's constructor
#include "FileManager.h"

// Start loading the texture in the background
std::future<bool> future = FileManager::LoadAsync<sf::Texture>("path/to/my/texture.png");

// In the scene's update method, you can check if the texture is loaded
void MyScene::update(sf::Time deltaTime) {
    if (future.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
        bool success = future.get();
        if (success) {
            // The texture is loaded, you can now use it.
            // For example, you could assign it to a sprite.
            mySprite.setTexture(AssetManager<sf::Texture>::getInstance().get("path/to/my/texture.png"));
        } else {
            // The texture failed to load.
        }
    }
}
```

In this example, `future.wait_for(std::chrono::seconds(0))` checks if the future has a value available without blocking. If it does, `future.get()` will retrieve the value.

### 3. A More Advanced Approach: A Loading Screen

A more sophisticated approach would be to create a dedicated loading screen that displays a progress bar while the assets are being loaded. Here's a high-level overview of how you could implement this:

1.  **Create a `LoadingScene`:** This scene would be responsible for loading all the assets for the next scene (e.g., the `GamePlayScene`).
2.  **Start Loading:** In the `LoadingScene`'s constructor, you would call `LoadAsync` for all the assets you need to load. You would store the returned `std::future` objects in a `std::vector`.
3.  **Update the Progress Bar:** In the `LoadingScene`'s `update` method, you would iterate through the vector of futures and check how many of them are ready. You would use this information to update a progress bar on the screen.
4.  **Transition to the Next Scene:** Once all the futures are ready, you would transition to the next scene.

This approach provides a much better user experience than simply freezing the game while assets are loading.

## Conclusion

Multi-threading can be a powerful tool for improving the performance and responsiveness of your game. Asynchronous asset loading is a great place to start, and the `FileManager` in this project is already set up to support it. As your game grows, you may find other opportunities to use multi-threading, such as for AI or physics calculations.
