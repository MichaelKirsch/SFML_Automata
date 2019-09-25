

#pragma once

#include "SFML/Graphics.hpp"
#include "World.h"
#include <vector>
class Creature {
public:
    Creature(sf::Vector2i spawnPos, unsigned int strength, unsigned int maxAge, unsigned int reproductionBonus);
    void update();
    sf::Vector3i getColor();
    sf::Vector2i getPosition();
    ~Creature();
private:
    sf::Vector2i m_positionInGrid;
    sf::Vector3i m_color;
    unsigned int m_strength;
    unsigned int m_age;
    unsigned int m_reproductionValue;
    unsigned int m_maxAge;
    unsigned int m_reproductionBonus;
};



