

#pragma once

#include "SFML/Graphics.hpp"
#include "World.h"
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "Util/RandomGenerator.h"

#define REPRODUCTION_THRESHOLD 40

class Creature {
public:
    Creature(sf::Vector2i spawnPos, unsigned int strength, unsigned int maxAge, unsigned int reproductionBonus);
    void update();
    void kill();
    bool canReproduce();
    int getMaxAge(){ return m_maxAge;};
    int getReprductionBonus(){ return m_reproductionBonus;};
    int getStrength(){return m_strength;};
    bool isAlive(){ return alive;};
    sf::Vector3i getColor();
    void ExpermentalSetColor(sf::Vector3i color){m_color = color;};
    sf::Vector2i getPosition();
    ~Creature();
private:
    bool alive;
    sf::Vector2i m_positionInGrid;
    sf::Vector3i m_color;
    unsigned int m_strength;
    unsigned int m_age;
    unsigned int m_reproductionValue;
    unsigned int m_maxAge;
    unsigned int m_reproductionBonus;
};



