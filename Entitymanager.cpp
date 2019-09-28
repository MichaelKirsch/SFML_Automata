

#include "Entitymanager.h"

Entitymanager::Entitymanager() {
}

Entitymanager::~Entitymanager() {

}

void Entitymanager::Draw(sf::RenderWindow &window) {
    window.draw(m_CreatureVertices);
}

void Entitymanager::spawnCreatures(int howMany)
{
    if(SOFTWARETEST)
    {
        spawnTest();
    } else
    {
        for (int creature = 0; creature < howMany; creature++)
        {
            sf::Vector2i rand_pos = custom_random_generator::getRandomPosition(1, p_world->m_worldSizeInTiles.x - 1, 1,
                                                                               p_world->m_worldSizeInTiles.y - 1);
            if (p_world->m_map[convertVectorToInt(rand_pos)] != World::BORDER && getPointerAtPosition(rand_pos) == nullptr)
            {
                Creature buffer = Creature(rand_pos, custom_random_generator::getRandomInt(10, 100),
                                           custom_random_generator::getRandomInt(10, 100),
                                           custom_random_generator::getRandomInt(0, 10));
                buffer.ExpermentalSetColor(custom_random_generator::getRandomColor());
                m_livingCreatures.push_back(buffer);
                m_CreaturePositions[convertVectorToInt(rand_pos)] = &m_livingCreatures.back();
            }
        }
    }
}


void Entitymanager::attachtoWorld(World& world) {
    this->p_world = &world;
    m_CreaturePositions.resize(p_world->m_map.size());
    m_CreaturePositions.assign(m_CreaturePositions.size(), nullptr); //fill the vector with nullpointers;
    long max_amount_vertices = 4*(p_world->m_map.size());
    m_CreatureVertices.setPrimitiveType(sf::Quads);
    m_CreatureVertices.resize(max_amount_vertices);
}


int Entitymanager::convertVectorToInt(sf::Vector2i pos) {
    return(p_world->m_worldSizeInTiles.y*pos.x)+pos.y;
}

void Entitymanager::updateVertexArray() {
    m_CreatureVertices.clear();
    std::vector<sf::Vector2f>creature_buffer;
    int m_tileSize = p_world->m_tileSize;
    int tile_creature_size_difference = m_tileSize*0.8;
    for(auto& item:m_livingCreatures)
    {
        sf::Vector2i pos = item.getPosition();
        creature_buffer.push_back(sf::Vector2f((float)((pos.x*m_tileSize)+tile_creature_size_difference),(float)((pos.y*m_tileSize)+tile_creature_size_difference)));
        creature_buffer.push_back(sf::Vector2f((float)(((pos.x+1)*m_tileSize)-tile_creature_size_difference),(float)((pos.y*m_tileSize)+tile_creature_size_difference)));
        creature_buffer.push_back(sf::Vector2f((float)(((pos.x+1)*m_tileSize)-tile_creature_size_difference),(float)(((pos.y+1)*m_tileSize)-tile_creature_size_difference)));
        creature_buffer.push_back(sf::Vector2f((float)((pos.x*m_tileSize)+tile_creature_size_difference),(float)(((pos.y+1)*m_tileSize)-tile_creature_size_difference)));
    }
    m_CreatureVertices.resize(creature_buffer.size());
    for(int x =0;x<creature_buffer.size();x++)
    {
        m_CreatureVertices[x].position = creature_buffer[x];
        sf::Vector3i color = m_livingCreatures[(int)x/4].getColor();
        m_CreatureVertices[x].color = sf::Color(color.x,color.y,color.z);
    }
}




void Entitymanager::Update() {
    if(!SOFTWARETEST)
    {
        updateCreatures();
    } else{
        updateTest();
    }
    
    updateVertexArray();
}

void Entitymanager::updateCreatures() {
    for(auto& creature:m_livingCreatures)
    {
       creature.update();
       if(creature.isAlive())
       {
           if(move(&creature)&&creature.canReproduce())
           {
               reproduce(&creature);
           }
       }

    }
    clearAllDeadCreatures();
}

bool Entitymanager::move(Creature* creature) {
    sf::Vector2i oldpos= creature->getPosition();
    sf::Vector2i newPos = custom_random_generator::generateMovePos(oldpos);
    if(isPositionValid(newPos)) //check if this position is even allowed
    {
        if(checkCollision(newPos))
        {
            //okay we have a collision lets figure out what to do
            Creature* creatureAtPosition =getPointerAtPosition(newPos);
            if(!checkFriendly(creature,creatureAtPosition))
            {
                clearPosition(oldpos);
                //okay its not a friend to lets fight
                if(!isHeWinningFight(creature,creatureAtPosition))
                {
                    //okay he lost
                    creature->kill();
                    return false;
                }
                else
                {
                    //okay he won the fight lets kill the oponent
                    creature->setPosition(newPos);
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
            creature->setPosition(newPos);
            clearPosition(oldpos);
            populatePosition(newPos,creature);
            return true;
        }
    }
    return false; //this was a move to a not allowed position
}

bool Entitymanager::checkCollision(sf::Vector2i posToCheck) {
    return (m_CreaturePositions[convertVectorToInt(posToCheck)] != nullptr);
}

bool Entitymanager::isHeWinningFight(Creature* creature, Creature* other_creature) {
    return other_creature->getStrength()<=creature->getStrength();
}

bool Entitymanager::checkFriendly(Creature* creature, Creature* other_creature) {
    return (creature->getColor() == other_creature->getColor());
}

void Entitymanager::populatePosition(sf::Vector2i position, Creature* creature) {
    m_CreaturePositions[convertVectorToInt(position)]=creature;
}

void Entitymanager::clearPosition(sf::Vector2i position) {
    m_CreaturePositions[convertVectorToInt(position)] = nullptr;
}

void Entitymanager::killCreature(sf::Vector2i position) {
    m_CreaturePositions[convertVectorToInt(position)]->kill();
}

void Entitymanager::reproduce(Creature* creature) {
    sf::Vector2i parentPos = creature->getPosition();
    sf::Vector2i childPos = custom_random_generator::generateMovePos(parentPos);
    if(!checkCollision(childPos) && isPositionValid(childPos))
    {
        //no collision so lets spawn a child
        spawnChild(creature,childPos, true);
    }
}

void Entitymanager::spawnChild(Creature* parent, sf::Vector2i childPos, bool mutate) {
    if(mutate)
    {
        Creature buffer = Creature(childPos,parent->getStrength()+custom_random_generator::getMutation(),parent->getMaxAge()+custom_random_generator::getMutation(),parent->getReprductionBonus()+custom_random_generator::getMutation());
        buffer.ExpermentalSetColor(parent->getColor());
        m_livingCreatures.push_back(buffer);
        populatePosition(childPos,&m_livingCreatures.back());
    }
    else
    {
        Creature buffer = Creature(childPos,parent->getStrength(),parent->getMaxAge(),parent->getReprductionBonus());
        buffer.ExpermentalSetColor(parent->getColor());
        m_livingCreatures.push_back(buffer);
        populatePosition(childPos,&m_livingCreatures.back());
    }
}

bool Entitymanager::isPositionValid(sf::Vector2i positionToCheck) {

    if(convertVectorToInt(positionToCheck) < 0 || convertVectorToInt(positionToCheck) > p_world->m_map.size())
    {
        std::cout<<positionToCheck.x<<"|"<<positionToCheck.y<< " out of vector, " <<convertVectorToInt(positionToCheck)<<std::endl;
        return false;
    }
    if(p_world->m_map[convertVectorToInt(positionToCheck)] == World::BORDER)
    {
        //printf("border");
        return false;
    }
    return true;
}

Creature *Entitymanager::getPointerAtPosition(sf::Vector2i position) {
    return m_CreaturePositions[convertVectorToInt(position)];
}

void Entitymanager::clearAllDeadCreatures() {
    for(int x=0;x<m_livingCreatures.size();x++)
    {
        if(!m_livingCreatures[x].isAlive())
        {
            clearPosition(m_livingCreatures[x].getPosition()); //kick out the old pointer
            m_livingCreatures.erase(m_livingCreatures.begin()+x); //delete the object
        }
    }
}

void Entitymanager::spawnTest() {
    for(int x =1;x<p_world->m_worldSizeInTiles.x;x++)
    {
        Creature buffer = Creature(sf::Vector2i(x,1),10,p_world->m_worldSizeInTiles.y-2,0);
        buffer.ExpermentalSetColor(custom_random_generator::getRandomColor());
        m_livingCreatures.push_back(buffer);
        m_CreaturePositions[convertVectorToInt(sf::Vector2i(x,1))] = &m_livingCreatures.back();
    }
    
}

void Entitymanager::updateTest() {
    for(auto& item:m_livingCreatures)
    {
        sf::Vector2i oldPos = item.getPosition();
        item.setPosition(sf::Vector2i(oldPos.x,oldPos.y+1));
    }
}


