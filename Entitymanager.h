

#pragma once


#include <SFML/Graphics.hpp>
#include "World.h"
#include <vector>
#include "Creature.h"
#include <iostream>
#include <map>
#define SOFTWARETEST false

class Entitymanager {
public:
    Entitymanager();
    void Draw(sf::RenderWindow& window);
    void attachtoWorld(World& world);
    void spawnCreatures(int howMany);
    void Update();
    unsigned int getNbrCreatures(){ return m_livingCreatures.size();};
    ~Entitymanager();

private:
    bool move (Creature* creature);
    bool isPositionValid(sf::Vector2i positionToCheck);
    void clearAllDeadCreatures();
    bool checkFriendly(Creature* creature,Creature* other_creature);
    bool checkCollision(sf::Vector2i posToCheck);
    Creature* getPointerAtPosition(sf::Vector2i position);
    void populatePosition(sf::Vector2i position, Creature* creature);
    void clearPosition(sf::Vector2i position);
    void killCreature(sf::Vector2i position);
    void reproduce(Creature* creature);
    void spawnChild(Creature* creature,sf::Vector2i childPos, bool mutate);
    bool isHeWinningFight(Creature* creature,Creature* other_creature);
    World * p_world;
    int convertVectorToInt(sf::Vector2i);
    void updateCreatures();
    void updateVertexArray();
    std::vector<Creature*>m_CreaturePositions;
    sf::VertexArray* p_CreatureVertices;
    sf::VertexArray m_CreatureVertices;
    std::vector<Creature>m_livingCreatures;
    std::vector<sf::Vector2f>m_creature_buffer;

//TESTS
private:
    void spawnTest();
    void updateTest();
};



