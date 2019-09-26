

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
    void attachtoWorld(World& world);
    void spawnCreatures(int howMany);
    void Update();
    unsigned int getNbrCreatures(){ return m_livingCreatures.size();};
    ~Entitiymanager();

private:
    bool checkCollision(Creature creature);
    bool fight(Creature creature);
    World * p_world;
    int convertVectorToInt(sf::Vector2i);
    void updateCreatures();
    void updateVertexArray();
    std::vector<Creature*>m_CreaturePositions;
    sf::VertexArray m_CreatureVertices;
    std::vector<Creature> m_livingCreatures;
protected:
};



