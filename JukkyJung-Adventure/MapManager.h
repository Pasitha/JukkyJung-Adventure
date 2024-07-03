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
     * @param tileWidth Width of each tile in pixels
     * @param tileHeight Height of each tile in pixels
     * @param rowSpriteCount Number of sprite rows in the tileset
     * @param colSpriteCount Number of sprite columns in the tileset
     * @param mapWidth Width of the map in tiles
     * @param mapHeight Height of the map in tiles
     * @param tileset Path to the tileset texture file
     */
    void addMap(const std::string& mapName, uint64_t tileWidth, uint64_t tileHeight, uint64_t rowSpriteCount, uint64_t colSpriteCount, uint64_t mapWidth, uint64_t mapHeight);

    void addLayer(const std::string& mapName, uint16_t layerID, const std::string& tileset);

    // Sets the scale for the specified map
    void setMapScale(const std::string& mapName, uint16_t layerID, const sf::Vector2f& scale);

    // Sets the default tile for the specified map
    void setDefaultTile(const std::string& mapName, uint16_t layerID, uint64_t defaultTileID);

    // Sets the tile map for the specified map using tile IDs from mapData
    void setTileMap(const std::string& mapName, int layerID, const std::string& tileset, const std::vector<std::vector<std::string>>& mapData);

    // void drawLayer(const std::string& mapName, int layerID);

    // Draws all maps managed by the MapManager
    void draw(const std::string& mapName);

private:
    // Struct representing a single map, including its properties and tile data
    struct Map {
        uint64_t tileWidth;
        uint64_t tileHeight;
        uint64_t mapWidth;
        uint64_t mapHeight;
        uint64_t rowSpriteCount;
        uint64_t colSpriteCount;

        // Each layer will have its own texture and tile sprites
        struct Layer {
            sf::Texture tileSetTexture;
            std::vector<sf::IntRect> tileTextureRect;
            std::vector<sf::Sprite> tileSprites;

            Layer() {}
        };

        std::unordered_map<uint16_t, Layer> layers;

        // Constructor to initialize a map with the specified dimensions and tile size
        Map() : tileWidth(0), tileHeight(0), rowSpriteCount(0), colSpriteCount(0), mapWidth(0), mapHeight(0) {}
        Map(uint64_t w, uint64_t h, uint64_t rsc, uint64_t cpc, uint64_t mw, uint64_t mh) 
            : tileWidth(w), tileHeight(h), rowSpriteCount(rsc), colSpriteCount(cpc), mapWidth(mw), mapHeight(mh) {}
    };

    sf::RenderWindow* windowInstance;        // Pointer to the SFML window for rendering

    std::unordered_map<std::string, std::shared_ptr<Map>> maps; // Unordered map of maps, keyed by their names
};
