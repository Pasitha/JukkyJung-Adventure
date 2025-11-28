#include "UIElementManager.h"
#include "UIElement.h"

UIElementManager::UIElementManager(sf::RenderWindow* window) : window(window) {}

UIElementManager::~UIElementManager() {}

void UIElementManager::addElement(std::unique_ptr<UIElement> element) {
    elements.push_back(std::move(element));
}

void UIElementManager::handleEvents(sf::Event& event) {
    for (auto& element : elements) {
        element->handleEvent(event);
    }
}

void UIElementManager::update(sf::Time deltaTime) {
    for (auto& element : elements) {
        element->update(deltaTime);
    }
}

void UIElementManager::draw() {
    for (auto& element : elements) {
        element->draw(*window);
    }
}
