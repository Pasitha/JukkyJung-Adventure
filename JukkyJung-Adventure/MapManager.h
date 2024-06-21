#pragma once
#include "common.h"

// MapManager class is responsible for managing multiple maps, setting tiles, and rendering the maps.
class MapManager {
public:
    // Constructor to initialize the MapManager with a reference to the SFML window
    MapManager(sf::RenderWindow* window);

    /**
     * Adds a new map with the specified parameters.
     * @param name Name of the map
     * @param width Width of the map in tiles
     * @param height Height of the map in tiles
     * @param tileSize Size of each tile in pixels
     * @param tileset Path to the tileset texture file
     */
    void addMap(const std::string& name, uint64_t tileWidth, uint64_t tileHeight, uint64_t rowSpriteCount, uint64_t colSpriteCount, uint64_t mapWidth, uint64_t mapHeight, const std::string& tileset);

    void setMapScale(const std::string& name, const sf::Vector2f& scale);

    void setTileMap(const std::string& name, const std::vector<std::vector<std::string>>& mapData);

    // Draws all maps managed by the MapManager
    void draw(const std::string& name);

private:
    // Struct representing a single map, including its properties and tile data
    struct Map {
        uint64_t tileWidth;
        uint64_t tileHeight;
        uint64_t mapWidth;
        uint64_t mapHeight;
        uint64_t rowSpriteCount;
        uint64_t colSpriteCount;
        sf::Texture tileSetTexture;
        std::vector<sf::IntRect> tileTextureRect;
        std::vector<sf::Sprite> tileSprites;

        // Constructor to initialize a map with the specified dimensions and tile size
        Map() : tileWidth(0), tileHeight(0), rowSpriteCount(0), colSpriteCount(0), mapWidth(0), mapHeight(0) {}
        Map(uint64_t w, uint64_t h, uint64_t rsc, uint64_t cpc, uint64_t mw, uint64_t mh) : tileWidth(w), tileHeight(h), rowSpriteCount(rsc), colSpriteCount(cpc), mapWidth(mw), mapHeight(mh) {}
    };

    sf::RenderWindow* windowInstance;        // Pointer to the SFML window for rendering

    std::unordered_map<std::string, std::shared_ptr<Map>> maps; // Unordered map of maps, keyed by their names
};
