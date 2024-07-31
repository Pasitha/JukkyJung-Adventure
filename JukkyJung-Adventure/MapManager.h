#pragma once
#include "common.h"

// MapManager class is responsible for managing multiple maps, setting tiles, and rendering the maps.
class MapManager {
public:
    /**
     * Constructor to initialize the MapManager with a reference to the SFML window.
     * @param window Pointer to the SFML window for rendering
     */
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
     */
    void addMap(const std::string& mapName, uint64_t tileWidth, uint64_t tileHeight, uint64_t rowSpriteCount, uint64_t colSpriteCount, uint64_t mapWidth, uint64_t mapHeight);

    /**
     * Adds a new layer to the specified map.
     * @param mapName Name of the map
     * @param layerID ID of the layer
     * @param tileset Path to the tileset texture file
     */
    void addLayer(const std::string& mapName, uint16_t layerID, const std::string& tileset);

    /**
     * Sets the scale for the specified map.
     * @param mapName Name of the map
     * @param scale Scale factor for the map
     */
    void setMapScale(const std::string& mapName, const sf::Vector2f& scale);

    /**
     * Sets the default tile for the specified layer in the map.
     * @param mapName Name of the map
     * @param layerID ID of the layer
     * @param defaultTileID ID of the default tile
     */
    void setDefaultTile(const std::string& mapName, uint16_t layerID, uint64_t defaultTileID);

    /**
     * Sets the tile map for the specified layer in the map using tile IDs from mapData.
     * @param mapName Name of the map
     * @param layerID ID of the layer
     * @param tileset Path to the tileset texture file
     * @param mapData 2D vector containing tile IDs
     */
    void setTileMap(const std::string& mapName, int layerID, const std::string& tileset, const std::vector<std::vector<std::string>>& mapData);

    /**
     * Sets a character to a specified position on a map.
     * @param mapName Name of the map
     * @param characterName Name of the character sprite
     * @param coordinateX X coordinate on the map
     * @param coordinateY Y coordinate on the map
     */
    void setCharacterToMap(const std::string& mapName, const std::string& characterName, int gridX, int gridY);

    void updateCharacterPosition(const std::string& characterName, int gridX, int gridY);

    sf::Vector2i getCharacterPosition(const std::string& characterName);

    void drawCharacters(SpriteAnimation* spriteAnimation);

    sf::Vector2f convertToWorldPosition(const sf::Vector2i& gridPosition);
    
    /**
     * Draws all maps managed by the MapManager.
     * @param mapName Name of the map to be drawn
     */
    void draw(const std::string& mapName);

    /**
     * Updates the camera view to follow the target.
     * @param targetPosition Position of the target to follow
     */
    void updateCamera(const sf::Vector2f& targetPosition);

private:
    // Struct representing a single map, including its properties and tile data
    struct Map {
        uint64_t tileWidth;       // Width of each tile in pixels
        uint64_t tileHeight;      // Height of each tile in pixels
        uint64_t mapWidth;        // Width of the map in tiles
        uint64_t mapHeight;       // Height of the map in tiles
        uint64_t rowSpriteCount;  // Number of sprite rows in the tileset
        uint64_t colSpriteCount;  // Number of sprite columns in the tileset

        // Each layer will have its own texture and tile sprites
        struct Layer {
            std::string tileSetTexturePath;        // Path to the tileset texture file
            std::vector<sf::IntRect> tileTextureRect; // Vector of tile texture rectangles
            std::vector<sf::Sprite> tileSprites;   // Vector of tile sprites

            // Default constructor for Layer
            Layer() {}
        };

        std::unordered_map<std::string, sf::Texture> tileSetTextures; // Map of tileset textures, keyed by their paths
        std::unordered_map<uint16_t, Layer> layers;                   // Map of layers, keyed by their IDs

        /**
         * Constructor to initialize a map with default values.
         */
        Map() : tileWidth(0), tileHeight(0), rowSpriteCount(0), colSpriteCount(0), mapWidth(0), mapHeight(0) {}

        /**
         * Constructor to initialize a map with the specified dimensions and tile size.
         * @param w Width of each tile in pixels
         * @param h Height of each tile in pixels
         * @param rsc Number of sprite rows in the tileset
         * @param cpc Number of sprite columns in the tileset
         * @param mw Width of the map in tiles
         * @param mh Height of the map in tiles
         */
        Map(uint64_t w, uint64_t h, uint64_t rsc, uint64_t cpc, uint64_t mw, uint64_t mh) 
            : tileWidth(w), tileHeight(h), rowSpriteCount(rsc), colSpriteCount(cpc), mapWidth(mw), mapHeight(mh) {}
    };

    // Struct representing a character in the game
    struct Character {
        std::string name;          // Name of the character
        sf::Sprite sprite;         // Sprite for the character
        uint16_t posX;             // X coordinate on the map
        uint16_t posY;             // Y coordinate on the map

        /**
         * Constructor to initialize a character with default values.
         */
        Character() : posX(0), posY(0) {}

        /**
         * Constructor to initialize a character with the specified parameters.
         * @param characterName Name of the character
         * @param characterSprite Sprite for the character
         * @param x X coordinate on the map
         * @param y Y coordinate on the map
         */
        Character(const std::string& characterName, const sf::Sprite& characterSprite, uint16_t x, uint16_t y)
            : name(characterName), sprite(characterSprite), posX(x), posY(y) {}
    };

    sf::RenderWindow* windowInstance;        // Pointer to the SFML window for rendering

    sf::View camera;                         // Camera view for the map

    std::unordered_map<std::string, std::shared_ptr<Map>> maps; // Unordered map of maps, keyed by their names

    std::map<std::string, sf::Vector2i> characters;  // Store characters and their grid positions
};
