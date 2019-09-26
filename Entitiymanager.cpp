

#include "Entitiymanager.h"

Entitiymanager::Entitiymanager() {

}

Entitiymanager::~Entitiymanager() {

}

void Entitiymanager::Draw(sf::RenderWindow &window) {
    window.draw(m_CreatureVertices);
}

void Entitiymanager::spawnCreatures(int howMany) {
    for(int creature=0;creature<howMany;creature++)
    {
        int x_position=(int)RandomFloat(0.0,(float)p_world->m_worldSizeInTiles.x);
        int y_position=(int)RandomFloat(0.0,(float)p_world->m_worldSizeInTiles.y);
        if(p_world->m_map[convertVectorToInt(sf::Vector2i(x_position,y_position))] == World::BORDER)
        {
            //std::cout << "position "<< x_position << "|" << y_position << "is a border" << std::endl;
        }
        else
        {
            Creature buffer = Creature(sf::Vector2i(x_position,y_position),19,(int)RandomFloat(0,1999),10);
            m_livingCreatures.push_back(buffer);
        }
    }
}

void Entitiymanager::setBoundaries(World& world) {
    this->p_world = &world;
}

float Entitiymanager::RandomFloat(float min, float max)
{
    float r = (float)rand() / (float)RAND_MAX;
    return min + r * (max - min);
}

int Entitiymanager::convertVectorToInt(sf::Vector2i pos) {
    return(p_world->m_worldSizeInTiles.y*pos.x)+pos.y;
}

void Entitiymanager::updateVertexArray() {
    std::vector<sf::Vector2f>creature_buffer;
    int m_tileSize = p_world->m_tileSize;
    int tile_creature_size_difference = m_tileSize*0.8;
    for(auto& item:m_livingCreatures)
    {
            int x_position = item.getPosition().x;
            int y_position = item.getPosition().y;
            creature_buffer.push_back(sf::Vector2f((x_position*m_tileSize)+tile_creature_size_difference,(y_position*m_tileSize)+tile_creature_size_difference));
            creature_buffer.push_back(sf::Vector2f(((x_position+1)*m_tileSize)-tile_creature_size_difference,(y_position*m_tileSize)+tile_creature_size_difference));
            creature_buffer.push_back(sf::Vector2f(((x_position+1)*m_tileSize)-tile_creature_size_difference,((y_position+1)*m_tileSize)-tile_creature_size_difference));
            creature_buffer.push_back(sf::Vector2f((x_position*m_tileSize)+tile_creature_size_difference,((y_position+1)*m_tileSize)-tile_creature_size_difference));
    }
    //std::cout<<creature_buffer.size()<<std::endl;
    m_CreatureVertices = sf::VertexArray(sf::Quads,creature_buffer.size()); // 4 vertices per creature
    for(int x =0;x<creature_buffer.size();x++)
    {
        m_CreatureVertices[x].position = creature_buffer[x];
        m_CreatureVertices[x].color = sf::Color((int)RandomFloat(0,255), (int)RandomFloat(0,255), (int)RandomFloat(0,255));
    }
}




void Entitiymanager::Update() {
    updateCreatures();
    updateVertexArray();
}

void Entitiymanager::updateCreatures() {
    for(auto& creature:m_livingCreatures)
    {
        creature.update();
        if(p_world->m_map[convertVectorToInt(creature.getPosition())]==World::BORDER)
        {
            creature.kill();
        }
    }


    for(int x=0;x<m_livingCreatures.size();x++)
    {
        if(!m_livingCreatures[x].isAlive())
        {
            std::cout<<&m_livingCreatures[x]<<" died"<<std::endl;
            m_livingCreatures.erase(m_livingCreatures.begin()+x);

        }
    }

}




