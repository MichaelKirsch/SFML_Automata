

#pragma once


#include <SFML/Graphics.hpp>
#include "World.h"
#include <vector>
#include "Creature.h"
#include <iostream>
#include <map>


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
    std::vector<sf::Vector2i> dirVectors;
    bool move (Creature creature);
    bool validatePosition(sf::Vector2i positionToCheck);
    bool checkFriendly(Creature creature,sf::Vector2i posToCheck);
    bool checkCollision(sf::Vector2i posToCheck);
    void populatePosition(sf::Vector2i position, Creature creature);
    void clearPosition(sf::Vector2i position);
    void killCreature(sf::Vector2i position);
    void reproduce(Creature creature);
    void spawnChild(Creature creature,sf::Vector2i childPos, bool mutate);
    bool isHeWinningFight(Creature creature, sf::Vector2i newPos);
    World * p_world;
    int convertVectorToInt(sf::Vector2i);
    void updateCreatures();
    void updateVertexArray();
    std::vector<Creature*>m_CreaturePositions;
    sf::VertexArray m_CreatureVertices;
    std::vector<Creature> m_livingCreatures;
protected:
};



