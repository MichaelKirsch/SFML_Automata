

#pragma once


#include <SFML/Graphics.hpp>
#include <vector>

class World {
//FUNCTIONS
public:
    World(sf::Vector2i worldSizeTiles,bool drawGrid,int tileSize);
    void Draw(sf::RenderWindow& window);
    ~World();
    void setWorldSizeTiles(sf::Vector2i world_size);
    void setdrawGrid(bool state);
    void settileSize(int size);
private:
    void m_BuildGrid();
//VARS
public:

private:
    bool m_drawGrid;
    int m_tileSize;
    sf::Vector2i m_worldSizeInTiles;
    sf::VertexArray m_overlayGrid;
};



