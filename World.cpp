

#include "World.h"
World::World(sf::Vector2i worldSizeTiles,int tileSize) {
    this->m_tileSize = tileSize;
    this->m_worldSizeInTiles = worldSizeTiles;
    this->m_drawGrid = true;
    createMap();
    if(m_drawGrid)
        m_BuildGrid();
}

World::~World() {

}

void World::Draw(sf::RenderWindow &window) {
    if(m_drawGrid)
        window.draw(m_overlayGrid);
    window.draw(m_borderGrid);
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
        m_overlayGrid[counter].color = sf::Color(
                65, 82, 89
        );
        counter++;
    }

    int vertexCountBorders = 16;
    m_borderGrid= sf::VertexArray(sf::Quads, vertexCountBorders);
    //left border
    m_borderGrid[0].position = sf::Vector2f(0.0f, 0.0f);
    m_borderGrid[1].position = sf::Vector2f(m_tileSize, 0.0f);
    m_borderGrid[2].position = sf::Vector2f(m_tileSize, m_worldSizeInTiles.y*m_tileSize);
    m_borderGrid[3].position = sf::Vector2f(0.0f, m_worldSizeInTiles.y*m_tileSize);

    //bottom border
    m_borderGrid[4].position = sf::Vector2f(0.0f, (m_worldSizeInTiles.y-1)*m_tileSize);
    m_borderGrid[5].position = sf::Vector2f(m_tileSize*m_worldSizeInTiles.x, (m_worldSizeInTiles.y-1)*m_tileSize);
    m_borderGrid[6].position = sf::Vector2f(m_tileSize*m_worldSizeInTiles.x, m_worldSizeInTiles.y*m_tileSize);
    m_borderGrid[7].position = sf::Vector2f(0.0f, m_worldSizeInTiles.y*m_tileSize);

    //right border
    m_borderGrid[8].position = sf::Vector2f((m_worldSizeInTiles.x-1)*m_tileSize, 0.0f);
    m_borderGrid[9].position = sf::Vector2f(m_tileSize*m_worldSizeInTiles.x, 0.0f);
    m_borderGrid[10].position = sf::Vector2f(m_tileSize*m_worldSizeInTiles.x, m_worldSizeInTiles.y*m_tileSize);
    m_borderGrid[11].position = sf::Vector2f((m_worldSizeInTiles.x-1)*m_tileSize, m_worldSizeInTiles.y*m_tileSize);

    //top border
    m_borderGrid[12].position = sf::Vector2f(0.0f, 0.0f);
    m_borderGrid[13].position = sf::Vector2f(m_tileSize*m_worldSizeInTiles.x, 0.0f);
    m_borderGrid[14].position = sf::Vector2f(m_tileSize*m_worldSizeInTiles.x, m_tileSize);
    m_borderGrid[15].position = sf::Vector2f(0.0f, m_tileSize);

    for(int vertex =0;vertex < vertexCountBorders;vertex++)
    {
        m_borderGrid[vertex].color = sf::Color(255, 101, 18);
    }


}

void World::setdrawGrid(bool state) {
    m_drawGrid = state;
}

std::vector<int> World::getMap() {
    return m_map;
}

void World::createMap() {
    for (int x_position=0;x_position<m_worldSizeInTiles.x;x_position++)
    {
        for (int y_position=0;y_position<m_worldSizeInTiles.y;y_position++)
        {
            if(x_position==0 || x_position==m_worldSizeInTiles.x-1 || y_position==0 || y_position==m_worldSizeInTiles.y-1)
            {
                m_map.push_back(BORDER);
            }
            else
            {
                m_map.push_back(GROUND);
            }
        }
    }
}

void World::toggleGrid() {
    m_drawGrid = !m_drawGrid;
}







