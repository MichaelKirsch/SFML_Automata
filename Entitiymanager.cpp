

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
        sf::Vector2i rand_pos = custom_random_generator::getRandomPosition(0,p_world->m_worldSizeInTiles.x,0,p_world->m_worldSizeInTiles.y);
        if(p_world->m_map[convertVectorToInt(rand_pos)] == World::BORDER)
        {
            //std::cout << "position "<< x_position << "|" << y_position << "is a border" << std::endl;
        }
        else
        {
            Creature buffer = Creature(rand_pos,19,custom_random_generator::getRandomInt(0,1000),10);
            buffer.ExpermentalSetColor(custom_random_generator::getRandomColor());
            m_livingCreatures.push_back(buffer);
        }
    }
}

void Entitiymanager::attachtoWorld(World& world) {
    this->p_world = &world;
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
        sf::Vector3i color = m_livingCreatures[(int)x/4].getColor();
        m_CreatureVertices[x].color = sf::Color(color.x,color.y,color.z);
    }
}




void Entitiymanager::Update() {
    updateCreatures();
    updateVertexArray();
    std::cout << "living creatures:"<<m_livingCreatures.size() << std::endl;
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
            //std::cout<<&m_livingCreatures[x]<<" died"<<std::endl;
            m_livingCreatures.erase(m_livingCreatures.begin()+x);

        }
    }

}




