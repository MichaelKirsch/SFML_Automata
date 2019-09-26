

#include "Creature.h"

Creature::~Creature() {

}

sf::Vector3i Creature::getColor() {
    return m_color;
}

sf::Vector2i Creature::getPosition() {
    return m_positionInGrid;
}

Creature::Creature(sf::Vector2i spawnPos, unsigned int strength, unsigned int maxAge, unsigned int reproductionBonus) {

    this->m_positionInGrid = spawnPos;
    this->m_strength = strength;
    this->m_maxAge = maxAge;
    this->m_reproductionBonus = reproductionBonus;
    alive = true;
    m_age=0;
    m_reproductionValue=reproductionBonus;
}

void Creature::update() {
    m_age++;
    m_reproductionValue++;
    int direction =custom_random_generator::getRandomInt(1,8);

    switch (direction)
    {
        case 8:
            m_positionInGrid.x+=0;
            m_positionInGrid.y+=1;
            break;

        case 1:
            m_positionInGrid.x+=1;
            m_positionInGrid.y+=1;
            break;
        case 2:
            m_positionInGrid.x+=-1;
            m_positionInGrid.y+=-1;
            break;
        case 3:
            m_positionInGrid.x+=0;
            m_positionInGrid.y+=-1;
            break;
        case 4:
            m_positionInGrid.x+=1;
            m_positionInGrid.y+=0;
            break;
        case 5:
            m_positionInGrid.x+=-1;
            m_positionInGrid.y+=0;
            break;
        case 6:
            m_positionInGrid.x+=0;
            m_positionInGrid.y+=1;
            break;
        case 7:
            m_positionInGrid.x+=0;
            m_positionInGrid.y+=0;
            break;
    }


    if(m_age>m_maxAge)
        alive= false;
}

void Creature::kill() {
    alive= false;
}


