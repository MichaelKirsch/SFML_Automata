

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Creature.h"


class World {
//FUNCTIONS
public:
    friend class Entitiymanager;
    World(sf::Vector2i worldSizeTiles,int tileSize);
    enum Tilestate{BORDER,GROUND,WATER,DESERT};
    void setdrawGrid(bool state);
    void printout(std::string whattoprint){std::cout<<whattoprint<<std::endl;};
    void Draw(sf::RenderWindow& window);
    void createMap();
    //TODO:void createMap(picture);
    ~World();
    std::vector<int> getMap();
private:
    void m_BuildGrid();

//VARS
private:
    std::vector<int>m_map;
    bool m_drawGrid;
    int m_tileSize;
    sf::Vector2i m_worldSizeInTiles;
    sf::VertexArray m_maptilesGrid;
    sf::VertexArray m_overlayGrid;
    sf::VertexArray m_borderGrid;
};



