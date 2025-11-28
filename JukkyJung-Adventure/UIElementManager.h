#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class UIElement;

class UIElementManager {
public:
    UIElementManager(sf::RenderWindow* window);
    ~UIElementManager();

    void addElement(std::unique_ptr<UIElement> element);
    void handleEvents(sf::Event& event);
    void update(sf::Time deltaTime);
    void draw();

private:
    sf::RenderWindow* window;
    std::vector<std::unique_ptr<UIElement>> elements;
};
