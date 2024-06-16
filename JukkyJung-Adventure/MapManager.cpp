#include "MapManager.h"

// Constructor to initialize the MapManager with a reference to the SFML window
MapManager::MapManager(sf::RenderWindow* window) : windowInstance(window) {}

// Adds a new map with the specified parameters
void MapManager::addMap(const std::string& name, int tileWidth, int tileHeight, int rowSpriteCount, int colSpriteCount, int mapWidth, int mapHeight, const std::string& tileset) {
    std::shared_ptr<Map> map = std::make_shared<Map>(tileWidth, tileHeight, mapWidth, mapHeight);

	// Loads the texture for the tileset of the specified map
    FileManager::LoadFromFile(map->tileSetTexture, tileset);

#ifdef _DEBUG
    std::cout << "MapWidth " << mapWidth / tileWidth << ", MapHeight " << mapHeight / tileHeight << std::endl;
#endif

    for (int col = 0; col < colSpriteCount; col++) {
        for (int row = 0; row < rowSpriteCount; row++) {
            sf::Sprite sprite;
            sprite.setTexture(map->tileSetTexture);
            sprite.setTextureRect(sf::IntRect(row * tileWidth, col * tileHeight, tileWidth, tileHeight));
            sprite.setPosition(sf::Vector2f(row * tileWidth, col * tileHeight));

            map->tileSprites.emplace_back(sprite);
        }
    }

    maps[name] = map;
}

// Draws all maps managed by the MapManager
void MapManager::draw(const std::string& name) {
    for (const auto& tile : maps[name]->tileSprites) {
        windowInstance->draw(tile);
    }
}
