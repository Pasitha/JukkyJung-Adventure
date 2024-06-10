#pragma once
#include "common.h"

class MapManager {
public:
    void addMap(const std::string& name, int width, int height, int tileSize, const std::string& tileset);
    void setTile(const std::string& name, int x, int y, int tileType);
    void draw(sf::RenderWindow& window);

private:
    struct Map {
        int width;
        int height;
        int tileSize;
        sf::Texture tilesetTexture;
        std::vector<int> tiles;
        std::vector<sf::Sprite> tileSprites;

        Map(int w, int h, int ts) : width(w), height(h), tileSize(ts), tiles(w * h, 0) {}
    };

    sf::RenderWindow* windowInstance;

    std::unordered_map<std::string, Map> m_maps;

    void loadTextures(Map& map, const std::string& tileset);
    void setTile(Map& map, int x, int y, int tileType);
    void drawMap(sf::RenderWindow& window, Map& map);
};
