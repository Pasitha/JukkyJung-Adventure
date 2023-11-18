#pragma once
#include "common.h"

class Component {
public:
    Component(sf::RenderWindow* window);
    virtual ~Component();

    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update() = 0;
    virtual void render() = 0;

protected:
    sf::RenderWindow* m_windowInstance;
};
