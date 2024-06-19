#include "MapManager.h"

// Constructor to initialize the MapManager with a reference to the SFML window
MapManager::MapManager(sf::RenderWindow* window) : windowInstance(window) {}

// Adds a new map with the specified parameters
void MapManager::addMap(const std::string& name, uint64_t tileWidth, uint64_t tileHeight, uint64_t rowSpriteCount, uint64_t colSpriteCount, uint64_t mapWidth, uint64_t mapHeight, const std::string& tileset) {
    // Create a new map with the specified dimensions and tile size
    std::shared_ptr<Map> map = std::make_shared<Map>(tileWidth, tileHeight, rowSpriteCount, colSpriteCount, mapWidth, mapHeight);

    // Load the texture for the tileset of the specified map
    FileManager::LoadFromFile(map->tileSetTexture, tileset);

    sf::Sprite sprite;
    sprite.setTexture(map->tileSetTexture);

    // Set texture rect and position for each tile sprite and add to the map
    for (uint64_t col = 0; col < colSpriteCount; ++col) {
        for (uint64_t row = 0; row < rowSpriteCount; ++row) {
            sprite.setTextureRect(sf::IntRect(row * tileWidth, col * tileHeight, tileWidth, tileHeight));
            sprite.setPosition(sf::Vector2f(row * tileWidth, col * tileHeight));
            map->tileSprites.emplace_back(sprite);
        }
    }

    // Add the new map to the maps collection
    maps[name] = map;
}

// Sets the scale for the specified map
void MapManager::setMapScale(const std::string& name, const sf::Vector2f& scale) {
    // Update scale, texture rect, and position for each tile sprite in the map
    for (uint64_t col = 0; col < maps[name]->colSpriteCount; ++col) {
        for (uint64_t row = 0; row < maps[name]->rowSpriteCount; ++row) {
            auto& sprite = maps[name]->tileSprites[col * maps[name]->rowSpriteCount + row];
            sprite.setScale(scale);
            sprite.setTextureRect(sf::IntRect(row * maps[name]->tileWidth, col * maps[name]->tileHeight, maps[name]->tileWidth, maps[name]->tileHeight));
            sprite.setPosition(sf::Vector2f(row * maps[name]->tileWidth * scale.x, col * maps[name]->tileHeight * scale.y));
        }
    }
}

// Draws the specified map
void MapManager::draw(const std::string& name) {
    // Draw each tile sprite in the map
    for (const auto& tile : maps[name]->tileSprites) {
        windowInstance->draw(tile);
    }
}
