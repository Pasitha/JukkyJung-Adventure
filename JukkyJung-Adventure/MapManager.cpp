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
            std::cout << col * rowSpriteCount + row << std::endl;
#endif
            sf::IntRect currentTileTexture = sf::IntRect(row * tileWidth, col * tileHeight, tileWidth, tileHeight);
            map->tileTextureRect.emplace_back(currentTileTexture);

        }
    }

	sf::Sprite sprite;
	sprite.setTexture(map->tileSetTexture);

    for (uint16_t col = 0; col < mapWidth; col++) {
        for (uint16_t row = 0; row < mapHeight; row++) {
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
            auto& sprite = maps[name]->tileSprites[col * maps[name]->mapHeight + row];
            sprite.setScale(scale);
            sprite.setPosition(sf::Vector2f(row * maps[name]->tileWidth * scale.x, col * maps[name]->tileHeight * scale.y));
        }
    }
}

void MapManager::setDefaultTile(const std::string& name, uint64_t defaultTileID) {
    for (uint64_t col = 0; col < maps[name]->mapHeight; col++) {
        for (uint64_t row = 0; row < maps[name]->mapWidth; row++) {
			auto& sprite = maps[name]->tileSprites[col * maps[name]->mapHeight + row];
			sprite.setTextureRect(maps[name]->tileTextureRect[defaultTileID]);
        }
    }
}

void MapManager::setTileMap(const std::string& name, const std::vector<std::vector<std::string>>& mapData) {
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

#ifdef TEST2
    int i = 0;
    for (const auto& dataVector : mapData) {
        for (const auto& data : dataVector) {
            short tileID = std::atoi(data.c_str());
#ifdef _DEBUG
            std::cout << "tileID: " << tileID << std::endl;
#endif
            if (tileID != -1) {
                auto& sprite = maps[name]->tileSprites[i++];
				sprite.setTextureRect(maps[name]->tileTextureRect[tileID]);
            }
        }
    }
#endif
}
    
// Draws the specified map
void MapManager::draw(const std::string& name) {
    // Draw each tile sprite in the map
    for (const auto& tile : maps[name]->tileSprites) {
        windowInstance->draw(tile);
    }
}
