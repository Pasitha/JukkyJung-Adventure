#include "MapManager.h"

// Constructor to initialize the MapManager with a reference to the SFML window
MapManager::MapManager(sf::RenderWindow& window) : windowInstance(&window) {}

// Adds a new map with the specified parameters
void MapManager::addMap(const std::string& name, int width, int height, int tileSize, const std::string& tileset) {
    Map newMap(width, height, tileSize);
    loadTextures(newMap, tileset);
    m_maps[name] = newMap;
}

// Loads the texture for the tileset of the specified map
void MapManager::loadTextures(Map& map, const std::string& tileset) {
    if (!map.tilesetTexture.loadFromFile(tileset)) {
        // Handle error
    }
}

// Sets the tile type at the specified position on the map
void MapManager::setTile(const std::string& name, int x, int y, int tileType) {
    auto it = m_maps.find(name);
    if (it != m_maps.end()) {
        setTile(it->second, x, y, tileType);
    }
}

// Sets the tile type at the specified position on the map
void MapManager::setTile(Map& map, int x, int y, int tileType) {
    if (x >= 0 && x < map.width && y >= 0 && y < map.height) {
        map.tiles[y * map.width + x] = tileType;

        // Create a sprite for this tile
        sf::Sprite sprite;
        sprite.setTexture(map.tilesetTexture);
        sprite.setTextureRect(sf::IntRect(tileType * map.tileSize, 0, map.tileSize, map.tileSize));
        sprite.setPosition(x * map.tileSize, y * map.tileSize);
        map.tileSprites.push_back(sprite);
    }
}

// Draws all maps managed by the MapManager
void MapManager::draw() {
    for (auto& pair : m_maps) {
        drawMap(pair.second);
    }
}

// Draws the specified map
void MapManager::drawMap(Map& map) {
    for (const auto& sprite : map.tileSprites) {
        windowInstance->draw(sprite);
    }
}

