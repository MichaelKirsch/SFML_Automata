

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Creature.h"

class World {
//FUNCTIONS
public:
    World(sf::Vector2i worldSizeTiles,bool drawGrid,int tileSize);
    void Draw(sf::RenderWindow& window);
    ~World();

private:
    void m_BuildGrid();
    void test_creature_grid();
//VARS
public:

private:
    std::vector<Creature>Creatures;
    bool m_drawGrid;
    int m_tileSize;
    sf::Vector2i m_worldSizeInTiles;
    sf::VertexArray m_creatureGrid;
    sf::VertexArray m_overlayGrid;
    sf::VertexArray m_borderGrid;
};



