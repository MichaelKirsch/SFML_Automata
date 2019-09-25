

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
    m_age=0;
    m_reproductionValue=reproductionBonus;
}

void Creature::update() {
    m_age++;
    m_reproductionValue++;
}



