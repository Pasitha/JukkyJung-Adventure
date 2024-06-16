#include "MapManager.h"

// Constructor to initialize the MapManager with a reference to the SFML window
MapManager::MapManager(sf::RenderWindow* window) : windowInstance(window) {}

// Adds a new map with the specified parameters
void MapManager::addMap(const std::string& name, uint64_t tileWidth, uint64_t tileHeight, uint64_t rowSpriteCount, uint64_t colSpriteCount, uint64_t mapWidth, uint64_t mapHeight, const std::string& tileset) {
    std::shared_ptr<Map> map = std::make_shared<Map>(tileWidth, tileHeight, rowSpriteCount, colSpriteCount, mapWidth, mapHeight);

	// Loads the texture for the tileset of the specified map
    FileManager::LoadFromFile(map->tileSetTexture, tileset);

#ifdef _DEBUG
    std::cout << "MapWidth " << mapWidth / tileWidth << ", MapHeight " << mapHeight / tileHeight << std::endl;
#endif

    for (uint64_t col = 0; col < colSpriteCount; col++) {
        for (uint64_t row = 0; row < rowSpriteCount; row++) {
            sf::Sprite sprite;
            sprite.setTexture(map->tileSetTexture);
            sprite.setTextureRect(sf::IntRect(row * tileWidth, col * tileHeight, tileWidth, tileHeight));
            sprite.setPosition(sf::Vector2f(row * tileWidth, col * tileHeight));

            map->tileSprites.emplace_back(sprite);
        }
    }

    maps[name] = map;
}

void MapManager::setMapScale(const std::string& name, const sf::Vector2f& scale) {
    for (uint64_t col = 0; col < maps[name]->colSpriteCount; col++) {
        for (uint64_t row = 0; row < maps[name]->rowSpriteCount; row++) {
			maps[name]->tileSprites[col * 32 + row].setScale(scale);
            maps[name]->tileSprites[col * 32 + row].setTextureRect(sf::IntRect(row * maps[name]->tileWidth, col * maps[name]->tileHeight, maps[name]->tileWidth, maps[name]->tileHeight));
            maps[name]->tileSprites[col * 32 + row].setPosition(sf::Vector2f(row * maps[name]->tileWidth * scale.y, col * maps[name]->tileHeight * scale.x));
        }
    }
}

// Draws all maps managed by the MapManager
void MapManager::draw(const std::string& name) {
    for (const auto& tile : maps[name]->tileSprites) {
        windowInstance->draw(tile);
    }
}
