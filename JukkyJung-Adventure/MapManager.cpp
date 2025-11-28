#include "MapManager.h"
#include <string>

MapManager::MapManager(sf::RenderWindow* window) : window(window), textureManager(AssetManager<sf::Texture>::getInstance()) {}

MapManager::~MapManager() {}

void MapManager::addMap(const std::string& mapName, int width, int height, int tileWidth, int tileHeight, int mapWidth, int mapHeight) {
    maps[mapName] = { {}, width, height, tileWidth, tileHeight, mapWidth, mapHeight, {1.f, 1.f} };
}

void MapManager::addLayer(const std::string& mapName, int layer, const std::string& texturePath) {
    maps[mapName].layers[layer] = { textureManager.get(texturePath), {} };
}

void MapManager::setDefaultTile(const std::string& mapName, int layer, int tile) {
    auto& map = maps[mapName];
    auto& layerRef = map.layers[layer];
    int textureWidth = layerRef.texture->getSize().x / map.tileWidth;

    for (int y = 0; y < map.mapHeight; ++y) {
        layerRef.tiles.emplace_back();
        for (int x = 0; x < map.mapWidth; ++x) {
            Tile newTile;
            newTile.tileType = tile;
            int tileX = (tile % textureWidth) * map.tileWidth;
            int tileY = (tile / textureWidth) * map.tileHeight;
            newTile.sprite.setTexture(*layerRef.texture);
            newTile.sprite.setTextureRect({ tileX, tileY, map.tileWidth, map.tileHeight });
            newTile.sprite.setPosition(x * map.tileWidth * map.scale.x, y * map.tileHeight * map.scale.y);
            newTile.sprite.setScale(map.scale);
            layerRef.tiles.back().push_back(newTile);
        }
    }
}

void MapManager::setTileMap(const std::string& mapName, int layer, const std::string& texturePath, const std::vector<std::vector<std::string>>& tileMap) {
    auto& map = maps[mapName];
    map.layers[layer].texture = textureManager.get(texturePath);
    auto& layerRef = map.layers[layer];
    int textureWidth = layerRef.texture->getSize().x / map.tileWidth;

    for (size_t y = 0; y < tileMap.size(); ++y) {
        if (y >= layerRef.tiles.size()) layerRef.tiles.emplace_back();
        for (size_t x = 0; x < tileMap[y].size(); ++x) {
            if (x >= layerRef.tiles[y].size()) layerRef.tiles[y].emplace_back();
            int tile = std::stoi(tileMap[y][x]);
            if (tile != -1) {
                Tile newTile;
                newTile.tileType = tile;
                int tileX = (tile % textureWidth) * map.tileWidth;
                int tileY = (tile / textureWidth) * map.tileHeight;
                newTile.sprite.setTexture(*layerRef.texture);
                newTile.sprite.setTextureRect({ tileX, tileY, map.tileWidth, map.tileHeight });
                newTile.sprite.setPosition(x * map.tileWidth * map.scale.x, y * map.tileHeight * map.scale.y);
                newTile.sprite.setScale(map.scale);
                layerRef.tiles[y][x] = newTile;
            }
        }
    }
}

void MapManager::setMapScale(const std::string& mapName, const sf::Vector2f& scale) {
    maps[mapName].scale = scale;
}

void MapManager::setCharacterToMap(const std::string& mapName, const std::string& characterName, int x, int y) {
    characterPositions[characterName] = { (float)x, (float)y };
}

void MapManager::updateCamera(const sf::Vector2f& playerPosition) {
    sf::View view = window->getView();
    view.setCenter(playerPosition);
    window->setView(view);
}

void MapManager::draw(const std::string& mapName) {
    for (auto const& [layer, layerData] : maps[mapName].layers) {
        for (auto const& row : layerData.tiles) {
            for (auto const& tile : row) {
                window->draw(tile.sprite);
            }
        }
    }
}
