#pragma once
#include <SFML/Graphics.hpp>

/**
 * @class Renderer
 * @brief A class that encapsulates all rendering operations.
 *
 * This class is responsible for managing the rendering process, including clearing the screen,
 * drawing objects, and displaying the final frame. It abstracts the low-level SFML
 * drawing calls, providing a cleaner and more organized rendering pipeline.
 */
class Renderer {
public:
    /**
     * @brief Constructs a Renderer object.
     * @param window The sf::RenderWindow to be used for rendering.
     */
    Renderer(sf::RenderWindow& window);

    /**
     * @brief Clears the render window with a default color.
     */
    void clear();

    /**
     * @brief Draws a drawable object to the render window.
     * @param drawable The object to be drawn.
     */
    void draw(const sf::Drawable& drawable);

    /**
     * @brief Displays the contents of the render window on the screen.
     */
    void display();

private:
    sf::RenderWindow& window;
};
