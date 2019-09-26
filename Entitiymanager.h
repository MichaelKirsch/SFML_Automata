

#pragma once


#include <SFML/Graphics.hpp>
#include "World.h"
#include <vector>
#include "Creature.h"
#include <iostream>


class Entitiymanager {
public:
    Entitiymanager();
    void Draw(sf::RenderWindow& window);
    void setBoundaries(World& world);
    void spawnCreatures(int howMany);
    void Update();
    unsigned int getNbrCreatures(){ return m_livingCreatures.size();};
    ~Entitiymanager();

private:
    World * p_world;
    float RandomFloat(float min, float max);
    sf::Vector2i generateNewPos(sf::Vector2i oldPos);
    int convertVectorToInt(sf::Vector2i);
    void updateCreatures();
    void updateVertexArray();
    std::vector<int>*m_map;
    sf::VertexArray m_CreatureVertices;
    std::vector<Creature> m_livingCreatures;
protected:
};



