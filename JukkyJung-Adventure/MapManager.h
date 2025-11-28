#pragma once
#include "common.h"
#include "AssetManager.h"

class MapManager {
public:
    MapManager(sf::RenderWindow* window);
    ~MapManager();

    void addMap(const std::string& mapName, int width, int height, int tileWidth, int tileHeight, int mapWidth, int mapHeight);
    void addLayer(const std::string& mapName, int layer, const std::string& texturePath);
    void setDefaultTile(const std::string& mapName, int layer, int tile);
    void setTileMap(const std::string& mapName, int layer, const std::string& texturePath, const std::vector<std::vector<std::string>>& tileMap);
    void setMapScale(const std::string& mapName, const sf::Vector2f& scale);
    void setCharacterToMap(const std::string& mapName, const std::string& characterName, int x, int y);
    void updateCamera(const sf::Vector2f& playerPosition);
    void draw(const std::string& mapName);

private:
    struct Tile {
        sf::Sprite sprite;
        int tileType;
    };

    struct Layer {
        sf::Texture* texture;
        std::vector<std::vector<Tile>> tiles;
    };

    struct Map {
        std::unordered_map<int, Layer> layers;
        int width;
        int height;
        int tileWidth;
        int tileHeight;
        int mapWidth;
        int mapHeight;
        sf::Vector2f scale;
    };

    sf::RenderWindow* window;
    std::unordered_map<std::string, Map> maps;
    std::unordered_map<std::string, sf::Vector2f> characterPositions;
    AssetManager<sf::Texture>& textureManager;
};
