#include "MapManager.h"

// Constructor to initialize the MapManager with a reference to the SFML window
MapManager::MapManager(sf::RenderWindow* window) : windowInstance(window) {}

// Adds a new map with the specified parameters
void MapManager::addMap(const std::string& mapName, uint64_t tileWidth, uint64_t tileHeight, uint64_t rowSpriteCount, uint64_t colSpriteCount, uint64_t mapWidth, uint64_t mapHeight) {
    // Create a new map with the specified dimensions and tile size
    std::shared_ptr<Map> map = std::make_shared<Map>(tileWidth, tileHeight, rowSpriteCount, colSpriteCount, mapWidth, mapHeight);

    // Add the new map to the maps collection
    maps[mapName] = map;
}

void MapManager::addLayer(const std::string& mapName, uint16_t layerID, const std::string& tileset) {
    auto& map = maps[mapName];
    auto& layer = map->layers[layerID];

    layer.tileSetTexturePath = tileset;

    // Load the texture if not already loaded
    if (map->tileSetTextures.find(tileset) == map->tileSetTextures.end()) {
		// Load the texture for the tileset
		FileManager::LoadFromFile(map->tileSetTextures[tileset], tileset);
    }

    // Set texture rect and position for each tile sprite
    for (uint64_t col = 0; col < map->colSpriteCount; col++) {
        for (uint64_t row = 0; row < map->rowSpriteCount; row++) {
            layer.tileTextureRect.emplace_back(sf::IntRect(row * map->tileWidth, col * map->tileHeight, map->tileWidth, map->tileHeight));
        }
    }

    sf::Sprite sprite;
    sprite.setTexture(map->tileSetTextures[tileset]);

    for (uint64_t col = 0; col < map->mapHeight; col++) {
        for (uint64_t row = 0; row < map->mapWidth; row++) {
            sprite.setPosition(sf::Vector2f(row * map->tileWidth, col * map->tileHeight));
            layer.tileSprites.emplace_back(sprite);
        }
    }
}

// Sets the scale for the specified map
void MapManager::setMapScale(const std::string& mapName, const sf::Vector2f& scale) {
    auto& map = maps[mapName];

    // Update scale, texture rect, and position for each tile sprite in the map
    for (auto& [layerID, layer] : map->layers) {
        for (uint64_t col = 0; col < map->mapHeight; ++col) {
            for (uint64_t row = 0; row < map->mapWidth; ++row) {
                auto& sprite = layer.tileSprites[col * map->mapWidth + row];
                sprite.setScale(scale);
                sprite.setPosition(sf::Vector2f(row * map->tileWidth * scale.x, col * map->tileHeight * scale.y));
            }
        }
    }
}

// Sets the default tile for the specified map
void MapManager::setDefaultTile(const std::string& mapName, uint16_t layerID, uint64_t defaultTileID) {
    auto& map = maps[mapName];
    auto& layer = map->layers[layerID];

    for (uint64_t col = 0; col < map->mapHeight; col++) {
        for (uint64_t row = 0; row < map->mapWidth; row++) {
            auto& sprite = layer.tileSprites[col * map->mapWidth + row];
            sprite.setTextureRect(layer.tileTextureRect[defaultTileID]);
        }
    }
}

// Sets the tile map for the specified map using tile IDs from mapData
void MapManager::setTileMap(const std::string& mapName, int layerID, const std::string& tileset, const std::vector<std::vector<std::string>>& mapData) {
    auto& map = maps[mapName];
    auto& layer = map->layers[layerID];

    // Error handling: Map data size mismatch
    if (mapData.size() != map->mapHeight || mapData[0].size() != map->mapWidth) {
        std::cerr << "Error: Map data dimensions (" << mapData.size() << "x" << mapData[0].size() << ") don't match map size (" << map->mapHeight << "x" << map->mapWidth << ")" << std::endl;
        return;
    }
#ifdef _DEBUG
    std::cout << "Map height: " << map->mapHeight << ", Map width: " << map->mapWidth << " total map size: " << map->mapWidth * map->mapHeight << std::endl;
#endif
    for (uint64_t col = 0; col < map->mapHeight; col++) {
        for (uint64_t row = 0; row < map->mapWidth; row++) {
            int16_t tileID = std::atoi(mapData[col][row].c_str());
            if (tileID != -1) {
                auto& sprite = layer.tileSprites[col * map->mapWidth + row];
                sprite.setTextureRect(layer.tileTextureRect[tileID]);
            }
        }
    }
}

// Draws the specified map managed by the MapManager
void MapManager::draw(const std::string& mapName) {
    // Draw each tile sprite in the map
    for (const auto& [layerID, Layer] : maps[mapName]->layers) {
		for (const auto& tile : Layer.tileSprites) {
			windowInstance->draw(tile);
		}
    }
}

