

#include "Entitiymanager.h"

Entitiymanager::Entitiymanager() {
    dirVectors.push_back(sf::Vector2i(1,0));
    dirVectors.push_back(sf::Vector2i(-1,0));
    dirVectors.push_back(sf::Vector2i(0,1));
    dirVectors.push_back(sf::Vector2i(0,-1));
}

Entitiymanager::~Entitiymanager() {

}

void Entitiymanager::Draw(sf::RenderWindow &window) {
    window.draw(m_CreatureVertices);
}

void Entitiymanager::spawnCreatures(int howMany)
{
    for (int creature = 0; creature < howMany; creature++) {
        sf::Vector2i rand_pos = custom_random_generator::getRandomPosition(1, p_world->m_worldSizeInTiles.x - 1, 1,
                                                                           p_world->m_worldSizeInTiles.y - 1);
        if (p_world->m_map[convertVectorToInt(rand_pos)] != World::BORDER) {
            Creature buffer = Creature(rand_pos, custom_random_generator::getRandomInt(0, 100),
                                       custom_random_generator::getRandomInt(0, 100),
                                       custom_random_generator::getRandomInt(0, 10));
            buffer.ExpermentalSetColor(custom_random_generator::getRandomColor());
            if (m_CreaturePositions[convertVectorToInt(rand_pos)] == nullptr) {
                m_livingCreatures.push_back(buffer);
                m_CreaturePositions[convertVectorToInt(rand_pos)] = &m_livingCreatures.back();
            }
        }
    }
}

void Entitiymanager::attachtoWorld(World& world) {
    this->p_world = &world;
    m_CreaturePositions.resize(p_world->m_map.size());
    m_CreaturePositions.assign(m_CreaturePositions.size(), nullptr); //fill the vector with nullpointers;
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
    m_CreatureVertices = sf::VertexArray(sf::Quads,creature_buffer.size()); // 4 vertices per creature
    for(int x=0;x<creature_buffer.size();x++)
    {
        m_CreatureVertices[x].position = creature_buffer[x];
        sf::Vector3i color = m_livingCreatures[(int)x/4].getColor();
        m_CreatureVertices[x].color = sf::Color(color.x,color.y,color.z);
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
       if(move(creature)&&creature.canReproduce())
           reproduce(creature); //if the creature moved successfully and cn reproduce then it should do so
    }
    for(int x=0;x<m_livingCreatures.size();x++)
    {
        if(!m_livingCreatures[x].isAlive())
        {
            m_CreaturePositions[convertVectorToInt(m_livingCreatures[x].getPosition())] = nullptr; //kick out the old pointer
            m_livingCreatures.erase(m_livingCreatures.begin()+x);
            x=0;
        }
    }
}

bool Entitiymanager::checkCollision(sf::Vector2i posToCheck) {
    return (m_CreaturePositions[convertVectorToInt(posToCheck)] != nullptr);
}

bool Entitiymanager::isHeWinningFight(Creature creature, sf::Vector2i newPos) {
    return m_CreaturePositions[convertVectorToInt(newPos)]->getStrength()<=creature.getStrength();
}

bool Entitiymanager::move(Creature creature) {
    int direction =custom_random_generator::getRandomInt(1,5)-1;
    sf::Vector2i oldpos= creature.getPosition();
    sf::Vector2i newPos = sf::Vector2i(oldpos.x+dirVectors[direction].x,oldpos.y+dirVectors[direction].y);
    if(validatePosition(newPos)) //check if this position is even allowed
    {
        if(checkCollision(newPos))
        {
            //okay we have a collision lets figure out what to do
            if(!checkFriendly(creature,newPos))
            {
                clearPosition(oldpos);
                //okay its not a friend to lets isHeWinningFight
                if(!isHeWinningFight(creature,newPos))
                {
                    //okay he lost
                    creature.kill();
                    return false;
                }
                else
                {
                    //okay he won the fight lets kill the oponent
                    creature.setPosition(newPos);
                    killCreature(newPos);
                    populatePosition(newPos,creature);
                    return true;
                }
            }
            //okay there is a friend, we dont move and dont reproduce (prevents overpopulation in that area)
            return false;
        }
        else
        {
            //okay its free so lets move there
            creature.setPosition(newPos);
            clearPosition(oldpos);
            populatePosition(newPos,creature);
            return true;
        }
    }
    return false; //this was a move to a not allowed position
}

bool Entitiymanager::checkFriendly(Creature creature,sf::Vector2i posToCheck) {
    return (creature.getColor() == m_CreaturePositions[convertVectorToInt(posToCheck)]->getColor());
}

void Entitiymanager::populatePosition(sf::Vector2i position, Creature creature) {
    m_CreaturePositions[convertVectorToInt(position)]=&creature;
}

void Entitiymanager::clearPosition(sf::Vector2i position) {
    m_CreaturePositions[convertVectorToInt(position)] = nullptr;
}

void Entitiymanager::killCreature(sf::Vector2i position) {
    m_CreaturePositions[convertVectorToInt(position)]->kill();
}

void Entitiymanager::reproduce(Creature creature) {
    sf::Vector2i parentPos = creature.getPosition();
    int direction =custom_random_generator::getRandomInt(1,5)-1;
    sf::Vector2i childPos = sf::Vector2i(parentPos.x+dirVectors[direction].x,parentPos.y+dirVectors[direction].y);
    if(!checkCollision(childPos)&&validatePosition(childPos))
    {
        //no collision so lets spawn a child
        spawnChild(creature,childPos, false);
    }
}

void Entitiymanager::spawnChild(Creature parent, sf::Vector2i childPos, bool mutate) {
    if(mutate)
    {
        //TODO mutation
    }
    else
    {
        Creature buffer = Creature(childPos,parent.getStrength(),parent.getMaxAge(),parent.getReprductionBonus());
        buffer.ExpermentalSetColor(parent.getColor());
        populatePosition(childPos,m_livingCreatures.emplace_back(buffer));
    }
}

bool Entitiymanager::validatePosition(sf::Vector2i positionToCheck) {
    return (convertVectorToInt(positionToCheck) > 0 && convertVectorToInt(positionToCheck) < p_world->m_map.size() &&
             p_world->m_map[convertVectorToInt(positionToCheck)] != World::BORDER);
}




