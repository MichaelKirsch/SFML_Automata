

#include "World.h"
World::World(sf::Vector2i worldSizeTiles, bool drawGrid,int tileSize) {
    this->m_tileSize = tileSize;
    this->m_worldSizeInTiles = worldSizeTiles;
    this->m_drawGrid = drawGrid;
    if(m_drawGrid)
        m_BuildGrid();
}

World::~World() {

}

void World::Draw(sf::RenderWindow &window) {
    if(m_drawGrid)
        window.draw(m_overlayGrid);
    //draw the rest of the stuff
}

void World::m_BuildGrid() {

    std::vector<sf::Vector2f> vertices;
    for(int x_position =0;x_position<m_worldSizeInTiles.x;x_position++)
    {
        vertices.push_back(sf::Vector2f((float)x_position*m_tileSize,0.0f));
        vertices.push_back(sf::Vector2f((float)x_position*m_tileSize,(float)m_worldSizeInTiles.y*m_tileSize));
    }
    for(int y_position =0;y_position<m_worldSizeInTiles.y;y_position++)
    {
        vertices.push_back(sf::Vector2f(0.0f,(float)y_position*m_tileSize));
        vertices.push_back(sf::Vector2f((float)m_worldSizeInTiles.x*m_tileSize,(float)y_position*m_tileSize));
    }

    int counter =0;
    m_overlayGrid = sf::VertexArray(sf::Lines,vertices.size());
    for(auto& entries:vertices)
    {
        m_overlayGrid[counter].position = entries;
        m_overlayGrid[counter].color = sf::Color::White;
        counter++;
    }

}

void World::setdrawGrid(bool draw) {
    this->m_drawGrid = draw;
}

void World::setWorldSizeTiles(sf::Vector2i worldsize) {
        this->m_worldSizeInTiles = worldsize;
}

void World::settileSize(int size) {
    this->m_tileSize = size;
}




