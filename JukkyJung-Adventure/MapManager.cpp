#include "MapManager.h"

// Constructor to initialize the MapManager with a reference to the SFML window
MapManager::MapManager(sf::RenderWindow* window) : windowInstance(window) {}

// Adds a new map with the specified parameters
void MapManager::addMap(const std::string& name, uint64_t tileWidth, uint64_t tileHeight, uint64_t rowSpriteCount, uint64_t colSpriteCount, uint64_t mapWidth, uint64_t mapHeight, const std::string& tileset) {
    // Create a new map with the specified dimensions and tile size
    std::shared_ptr<Map> map = std::make_shared<Map>(tileWidth, tileHeight, rowSpriteCount, colSpriteCount, mapWidth, mapHeight);

    // Load the texture for the tileset of the specified map
    FileManager::LoadFromFile(map->tileSetTexture, tileset);

    // Set texture rect and position for each tile sprite and add to the map
    for (uint64_t col = 0; col < colSpriteCount; col++) {
        for (uint64_t row = 0; row < rowSpriteCount; row++) {
#ifdef _DEBUG
            std::cout << "push new sprite ID: " << col * rowSpriteCount + row << std::endl;
#endif
            map->tileTextureRect.emplace_back(sf::IntRect(row * tileWidth, col * tileHeight, tileWidth, tileHeight));
        }
    }

    sf::Sprite sprite;
    sprite.setTexture(map->tileSetTexture);

    for (uint16_t col = 0; col < mapHeight; col++) {
        for (uint16_t row = 0; row < mapWidth; row++) {
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
    for (uint64_t col = 0; col < maps[name]->mapHeight; ++col) {
        for (uint64_t row = 0; row < maps[name]->mapWidth; ++row) {
            auto& sprite = maps[name]->tileSprites[col * maps[name]->mapWidth + row];
            sprite.setScale(scale);
            sprite.setPosition(sf::Vector2f(row * maps[name]->tileWidth * scale.x, col * maps[name]->tileHeight * scale.y));
        }
    }
}

// Sets the default tile for the specified map
void MapManager::setDefaultTile(const std::string& name, uint64_t defaultTileID) {
    for (uint64_t col = 0; col < maps[name]->mapHeight; col++) {
        for (uint64_t row = 0; row < maps[name]->mapWidth; row++) {
            auto& sprite = maps[name]->tileSprites[col * maps[name]->mapWidth + row];
            sprite.setTextureRect(maps[name]->tileTextureRect[defaultTileID]);
        }
    }
}

// Sets the tile map for the specified map using tile IDs from mapData
void MapManager::setTileMap(const std::string& name, const std::vector<std::vector<std::string>>& mapData) {
    // Error handling: Map data size mismatch
    if (mapData.size() != maps[name]->mapHeight || mapData[0].size() != maps[name]->mapWidth) {
        std::cerr << "Error: Map data dimensions (" << mapData.size() << "x" << mapData[0].size() << ") don't match map size (" << maps[name]->mapHeight << "x" << maps[name]->mapWidth << ")" << std::endl;
        return;
    }
#ifdef _DEBUG
    std::cout << "Map height: " << maps[name]->mapHeight << ", Map width: " << maps[name]->mapWidth << " total map size: " << maps[name]->mapWidth * maps[name]->mapHeight << std::endl;
#endif
    for (uint64_t col = 0; col < maps[name]->mapHeight; col++) {
        for (uint64_t row = 0; row < maps[name]->mapWidth; row++) {
            short tileID = std::atoi(mapData[col][row].c_str());
#ifdef _DEBUG
            std::cout << "col: " << col << " row: " << row << " at index " << col * maps[name]->mapWidth + row << " current tileID : " << tileID << std::endl;
#endif

            if (tileID != -1) {
                auto& sprite = maps[name]->tileSprites[col * maps[name]->mapWidth + row];
                sprite.setTextureRect(maps[name]->tileTextureRect[tileID]);
            }
        }
    }
}

// Draws the specified map managed by the MapManager
void MapManager::draw(const std::string& name) {
    // Draw each tile sprite in the map
    for (const auto& tile : maps[name]->tileSprites) {
        windowInstance->draw(tile);
    }
}

