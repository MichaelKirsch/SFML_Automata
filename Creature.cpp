

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
    if(m_age>m_maxAge)
    {
        alive= false;
    }

}

void Creature::kill() {
    alive= false;
}

bool Creature::canReproduce() {
    if(m_reproductionValue>REPRODUCTION_THRESHOLD)
    {
        m_reproductionValue=m_reproductionBonus;
        return true;
    }
    return false;
}


