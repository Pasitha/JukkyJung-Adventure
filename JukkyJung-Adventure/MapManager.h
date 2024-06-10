#pragma once
#include "common.h"

// MapManager class is responsible for managing multiple maps, setting tiles, and rendering the maps.
class MapManager {
public:
    // Constructor to initialize the MapManager with a reference to the SFML window
    MapManager(sf::RenderWindow& window);

    /**
     * Adds a new map with the specified parameters.
     * @param name Name of the map
     * @param width Width of the map in tiles
     * @param height Height of the map in tiles
     * @param tileSize Size of each tile in pixels
     * @param tileset Path to the tileset texture file
     */
    void addMap(const std::string& name, int width, int height, int tileSize, const std::string& tileset);

    /**
     * Sets the tile type at the specified position on the map.
     * @param name Name of the map
     * @param x X-coordinate of the tile
     * @param y Y-coordinate of the tile
     * @param tileType Type of the tile
     */
    void setTile(const std::string& name, int x, int y, int tileType);

    // Draws all maps managed by the MapManager
    void draw();

private:
    // Struct representing a single map, including its properties and tile data
    struct Map {
        int width;                           // Width of the map in tiles
        int height;                          // Height of the map in tiles
        int tileSize;                        // Size of each tile in pixels
        sf::Texture tilesetTexture;          // Texture of the tileset
        std::vector<int> tiles;              // Vector of tile types
        std::vector<sf::Sprite> tileSprites; // Vector of tile sprites

        // Constructor to initialize a map with the specified dimensions and tile size
        Map() : width(0), height(0), tileSize(0), tiles(0, 0) {}
        Map(int w, int h, int ts) : width(w), height(h), tileSize(ts), tiles(w * h, 0) {}
    };

    sf::RenderWindow* windowInstance;        // Pointer to the SFML window for rendering

    std::unordered_map<std::string, Map> m_maps; // Unordered map of maps, keyed by their names

    /**
     * Loads the texture for the tileset of the specified map.
     * @param map Reference to the map
     * @param tileset Path to the tileset texture file
     */
    void loadTextures(Map& map, const std::string& tileset);

    /**
     * Sets the tile type at the specified position on the map.
     * @param map Reference to the map
     * @param x X-coordinate of the tile
     * @param y Y-coordinate of the tile
     * @param tileType Type of the tile
     */
    void setTile(Map& map, int x, int y, int tileType);

    /**
     * Draws the specified map.
     * @param map Reference to the map
     */
    void drawMap(Map& map);
};
