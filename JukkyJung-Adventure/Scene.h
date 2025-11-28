#pragma once
#include "common.h"
#include <SFML/Graphics.hpp>

// Forward declarations
class Game;
class Renderer;

/**
 * @class Scene
 * @brief An abstract base class for all game scenes.
 *
 * This class defines the interface that all scenes (like the main menu, gameplay, etc.)
 * must implement. It ensures that the Game class can handle any scene in a uniform way.
 */
class Scene {
public:
    /**
     * @enum Type
     * @brief Defines the different types of scenes available in the game.
     */
    enum Type {
        MainMenu,
        GamePlay,
        Setting,
        PauseMenu
    };

    virtual ~Scene() = default;

    /**
     * @brief Handles events for the scene.
     * @param event The SFML event to be processed.
     */
    virtual void handleEvents(sf::Event& event) = 0;

    /**
     * @brief Updates the scene's logic.
     * @param deltaTime The time elapsed since the last frame.
     */
    virtual void update(sf::Time deltaTime) = 0;

    /**
     * @brief Renders the scene to the screen.
     * @param renderer The renderer to be used for drawing.
     */
    virtual void render(Renderer& renderer) = 0;
};
