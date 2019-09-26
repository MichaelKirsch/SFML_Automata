#pragma once
#include <SFML/Graphics.hpp>
#include "World.h"
#include <iostream>
#include "Entitiymanager.h"
#include "Util/RandomGenerator.h"

#define WIDTH 1000
#define HEIGHT 1000

#define TILEMAP_X 100
#define TILEMAP_Y 100
#define TILESIZE 32

class Game {
//VARS
private:
    World world;
    Entitiymanager entMgr;
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



