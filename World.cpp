

#include "World.h"
World::World(sf::Vector2i worldSizeTiles, bool drawGrid,int tileSize) {
    this->m_tileSize = tileSize;
    this->m_worldSizeInTiles = worldSizeTiles;
    this->m_drawGrid = drawGrid;
    test_creature_grid();//TODO just a test
    if(m_drawGrid)
        m_BuildGrid();
}

World::~World() {

}

void World::Draw(sf::RenderWindow &window) {
    if(m_drawGrid)
        window.draw(m_overlayGrid);
    window.draw(m_borderGrid);
    window.draw(m_creatureGrid);
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

void World::test_creature_grid() {
    int tile_creature_size_difference = 4.0f;
    std::vector<sf::Vector2f>creature_buffer;
    for(int x_position=1;x_position<(m_worldSizeInTiles.x-1);x_position++)
    {
        for(int y_position=1;y_position<(m_worldSizeInTiles.y-1);y_position++)
        {
            creature_buffer.push_back(sf::Vector2f((x_position*m_tileSize)+tile_creature_size_difference,(y_position*m_tileSize)+tile_creature_size_difference));
            creature_buffer.push_back(sf::Vector2f(((x_position+1)*m_tileSize)-tile_creature_size_difference,(y_position*m_tileSize)+tile_creature_size_difference));
            creature_buffer.push_back(sf::Vector2f(((x_position+1)*m_tileSize)-tile_creature_size_difference,((y_position+1)*m_tileSize)-tile_creature_size_difference));
            creature_buffer.push_back(sf::Vector2f((x_position*m_tileSize)+tile_creature_size_difference,((y_position+1)*m_tileSize)-tile_creature_size_difference));
        }
    }
    std::cout<<creature_buffer.size()<<std::endl;
    m_creatureGrid = sf::VertexArray(sf::Quads,creature_buffer.size()); // 4 vertices per creature
    for(int x =0;x<creature_buffer.size();x++)
    {
        m_creatureGrid[x].position = creature_buffer[x];
        m_creatureGrid[x].color = sf::Color(3, 252, 252);
    }

}





