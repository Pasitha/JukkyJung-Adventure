#include "MapManager.h"

// Constructor to initialize the MapManager with a reference to the SFML window
MapManager::MapManager(sf::RenderWindow* window) : windowInstance(window) {}

// Adds a new map with the specified parameters
void MapManager::addMap(const std::string& name, int tileWidth, int tileHeight, int mapWidth, int mapHeight, const std::string& tileset) {
    Map map(tileWidth, tileHeight, mapWidth, mapHeight);

	// Loads the texture for the tileset of the specified map
    FileManager::LoadFromFile(map.tilesetTexture, tileset);

    for (int row = 0; row < mapWidth / tileWidth; row++) {
        for (int col = 0; col < mapHeight / tileHeight; col++) {
            sf::Sprite sprite;
            sprite.setTexture(map.tilesetTexture);
            sprite.setTextureRect(sf::IntRect(row * tileWidth, 0, col * tileHeight, col * tileHeight));
            sprite.setPosition(sf::Vector2<float>(row * tileWidth, col * tileHeight));

            map.tileSprites.push_back(sprite);
        }
    }

    maps[name] = map;
}

// Draws all maps managed by the MapManager
void MapManager::draw() {
    for (const auto& pair : maps) {
        for (const auto& tile : pair.second.tileSprites) {
			windowInstance->draw(tile);
        }
    }
}

// Draws the specified map
void MapManager::drawMap(Map& map) {
    for (const auto& sprite : map.tileSprites) {
        windowInstance->draw(sprite);
    }
}

