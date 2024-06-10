#include "MapManager.h"

void MapManager::addMap(const std::string& name, int width, int height, int tileSize, const std::string& tileset) {
    Map newMap(width, height, tileSize);
    loadTextures(newMap, tileset);
    m_maps[name] = newMap;
}

void MapManager::loadTextures(Map& map, const std::string& tileset) {
    FileManager::LoadFromFile(map.tilesetTexture, tileset);
}

void MapManager::setTile(const std::string& name, int x, int y, int tileType) {
    auto it = m_maps.find(name);
    if (it != m_maps.end()) {
        setTile(it->second, x, y, tileType);
    }
}

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

void MapManager::draw(sf::RenderWindow& window) {
    for (auto& pair : m_maps) {
        drawMap(window, pair.second);
    }
}

void MapManager::drawMap(sf::RenderWindow& window, Map& map) {
    for (const auto& sprite : map.tileSprites) {
        window.draw(sprite);
    }
}
