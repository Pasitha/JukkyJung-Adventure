#include "Renderer.h"
#include <SFML/Graphics.hpp>

Renderer::Renderer(sf::RenderWindow& window) : window(window) {}

void Renderer::clear() {
    window.clear(sf::Color(199, 119, 19, 255));
}

void Renderer::draw(const sf::Drawable& drawable) {
    window.draw(drawable);
}

void Renderer::display() {
    window.display();
}
