#pragma once
#include <SFML/Graphics.hpp>
#include "World.h"
#include <iostream>
#include "Entitymanager.h"
#include "Util/RandomGenerator.h"

#define WIDTH 1000
#define HEIGHT 1000

#define TILEMAP_X 100
#define TILEMAP_Y 100
#define TILESIZE 32

#define HOW_MANY_CREATURES_AT_START 10

class Game {
//VARS
private:
    World world;
    Entitymanager entMgr;
    sf::View view;
    sf::RenderWindow window;
//FUNCTIONS
public:
    Game();
    ~Game();
    void run();
private:
    float time_passed;
    void update(sf::Time elapsed);
    void processEvents();
    void render();
};



