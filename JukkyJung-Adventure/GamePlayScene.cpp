#include "GamePlayScene.h"
#include "Game.h"
#include "Button.h"
#include "Renderer.h"
#include "Combat.h"
#include "Character.h"
#include "Enemy.h"

GamePlayScene::GamePlayScene(sf::RenderWindow* window) : isInCombat(false) {
    uiElement = std::make_unique<UIElementManager>(window);

    auto attackButton = std::make_unique<Button>("ATTACK", Game::getInstance()->getFont(), sf::Vector2f(50, 800), [this](){
        if (isInCombat) {
            combat->playerAttack();
        }
    });
    uiElement->addElement(std::move(attackButton));

    auto itemButton = std::make_unique<Button>("ITEM", Game::getInstance()->getFont(), sf::Vector2f(400, 800), [this](){
        if (isInCombat) {
            // combat->playerUseItem("some_item");
        }
    });
    uiElement->addElement(std::move(itemButton));

    auto skipButton = std::make_unique<Button>("SKIP ROUND", Game::getInstance()->getFont(), sf::Vector2f(750, 800), [](){});
    uiElement->addElement(std::move(skipButton));

    auto startCombatButton = std::make_unique<Button>("Start Combat", Game::getInstance()->getFont(), sf::Vector2f(1200, 800), [this](){
        auto player = std::make_unique<Character>("JukkyJung", 100, 20);
        auto enemy = std::make_unique<Enemy>("Zombie", 50, 10);
        combat = std::make_unique<Combat>(std::move(player), std::move(enemy));
        isInCombat = true;
    });
    uiElement->addElement(std::move(startCombatButton));

    spriteAnimation = std::make_unique<SpriteAnimation>(window);
    map = std::make_unique<MapManager>(window);

    spriteAnimation->loadSpriteSheet("asset/JukkyJung-Sprite.png", "JukkyJung", { 64, 64 }, 24, {1000, 220});
    spriteAnimation->setScale("JukkyJung", { 2.f, 2.f });
    spriteAnimation->setState("JukkyJung", "Spellcast-back", 0, 7, .35f);
    spriteAnimation->setState("JukkyJung", "Spellcast-left", 1, 7, .35f);
    spriteAnimation->setState("JukkyJung", "Spellcast-front", 2, 7, .35f);
    spriteAnimation->setState("JukkyJung", "Spellcast-right", 3, 7, .35f);
    spriteAnimation->setState("JukkyJung", "Walk-back", 8, 1, 8, .15f);
    spriteAnimation->setState("JukkyJung", "Walk-left", 9, 1, 8, .15f);
    spriteAnimation->setState("JukkyJung", "Walk-front", 10, 1, 8, .15f);
    spriteAnimation->setState("JukkyJung", "Walk-right", 11, 1, 8, .15f);
    spriteAnimation->changeState("JukkyJung", "Spellcast-front");

    spriteAnimation->loadSpriteSheet("asset/Zombie-Sprite.png", "Dummy1", { 64, 64 }, 36, {1500, 220});
    spriteAnimation->setScale("Dummy1", { 2.f, 2.f });
    spriteAnimation->setState("Dummy1", "Walk-left", 9, 8, .35f);
    spriteAnimation->changeState("Dummy1", "Walk-left");

    spriteAnimation->loadSpriteSheet("asset/Zombie-Sprite.png", "Dummy2", { 64, 64 }, 36, {200, 480});
    spriteAnimation->setScale("Dummy2", { 2.f, 2.f });
    spriteAnimation->setState("Dummy2", "Walk-right", 11, 8, .35f);
    spriteAnimation->changeState("Dummy2", "Walk-right");

    spriteAnimation->loadSpriteSheet("asset/Headman-Sprite.png", "Headman", { 64, 64 }, 36, {960, 730});
    spriteAnimation->setScale("Headman", { 2.f, 2.f });
    spriteAnimation->setState("Headman", "Idel-right", 15, 1, 2, .75f);
    spriteAnimation->changeState("Headman", "Idel-right");

    map->addMap("village", 32, 32, 32, 32, 60, 34);
    map->addLayer("village", 0, "asset/terrain_atlas.png");
    map->addLayer("village", 1, "asset/terrain_atlas.png");
    map->addLayer("village", 2, "asset/terrain_atlas.png");
    map->setDefaultTile("village", 0, 112);
    map->setDefaultTile("village", 1, 224);
    map->setDefaultTile("village", 2, 224);
    map->setTileMap("village", 1, "asset/terrain_atlas.png", FileManager::ParseCSV("asset/village._ground_grass_decorate.csv"));
    map->setTileMap("village", 2, "asset/terrain_atlas.png", FileManager::ParseCSV("asset/village._ground_water path.csv"));
    map->setMapScale("village", { 2.f, 2.f });

    map->setCharacterToMap("village", "Headman", 5, 5);
}

GamePlayScene::~GamePlayScene() {}

void GamePlayScene::handleEvents(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        Game::getInstance()->changeScene(Scene::PauseMenu);
    }
    uiElement->handleEvents(event);
}

void GamePlayScene::update(sf::Time deltaTime) {
    if (!isInCombat) {
        handlePlayerMovement(deltaTime);
    }
    spriteAnimation->updateAnimation("JukkyJung", deltaTime.asSeconds());
    spriteAnimation->updateAnimation("Dummy1", deltaTime.asSeconds());
    spriteAnimation->updateAnimation("Dummy2", deltaTime.asSeconds());
    spriteAnimation->updateAnimation("Headman", deltaTime.asSeconds());
    sf::Vector2f playerPosition = spriteAnimation->getPosition("JukkyJung");
    map->updateCamera(playerPosition);
    uiElement->update(deltaTime);
}

void GamePlayScene::render(Renderer& renderer) {
    map->draw("village");
    spriteAnimation->drawAnimation("JukkyJung");
    spriteAnimation->drawAnimation("Dummy1");
    spriteAnimation->drawAnimation("Dummy2");
    spriteAnimation->drawAnimation("Headman");
    uiElement->draw();
}

void GamePlayScene::handlePlayerMovement(sf::Time deltaTime) {
    sf::Vector2f movement(0.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		movement.y = -100.f;
		spriteAnimation->changeState("JukkyJung", "Walk-back");
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		movement.x = -100.f;
		spriteAnimation->changeState("JukkyJung", "Walk-left");
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		movement.y = 100.f;
		spriteAnimation->changeState("JukkyJung", "Walk-front");
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		movement.x = 100.f;
		spriteAnimation->changeState("JukkyJung", "Walk-right");
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		movement.x = -65.f * sqrtf(2.f);
		movement.y = -65.f * sqrtf(2.f);
		spriteAnimation->changeState("JukkyJung", "Walk-left");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		movement.x = 65.f * sqrtf(2.f);
		movement.y = -65.f * sqrtf(2.f);
		spriteAnimation->changeState("JukkyJung", "Walk-right");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		movement.x = -65.f * sqrtf(2.f);
		movement.y = 65.f * sqrtf(2.f);
		spriteAnimation->changeState("JukkyJung", "Walk-left");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		movement.x = 65.f * sqrtf(2.f);
		movement.y = 65.f * sqrtf(2.f);
		spriteAnimation->changeState("JukkyJung", "Walk-right");
	}

	if (movement.x != 0.f || movement.y != 0.f) {
		spriteAnimation->moveSprite("JukkyJung", movement * deltaTime.asSeconds());
	}
}
