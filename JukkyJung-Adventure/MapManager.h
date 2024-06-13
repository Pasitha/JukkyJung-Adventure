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
    void addMap(const std::string& name, int tileWidth, int tileHeight, int mapWidth, int mapHeight, const std::string& tileset);

    // Draws all maps managed by the MapManager
    void draw();

private:
    // Struct representing a single map, including its properties and tile data
    struct Map {
        int tileWidth;
        int tileHeight;
        int mapWidth;
        int mapHeight;
        sf::Texture tilesetTexture;
        std::vector<sf::Sprite> tileSprites;

        // Constructor to initialize a map with the specified dimensions and tile size
        Map() : tileWidth(0), tileHeight(0), mapWidth(0), mapHeight(0) {}
        Map(int w, int h, int mw, int mh) : tileWidth(w), tileHeight(h), mapWidth(mw), mapHeight(mh) {}
    };

    sf::RenderWindow* windowInstance;        // Pointer to the SFML window for rendering

    std::unordered_map<std::string, Map> maps; // Unordered map of maps, keyed by their names

    /**
     * Draws the specified map.
     * @param map Reference to the map
     */
    void drawMap(Map& map);
};
