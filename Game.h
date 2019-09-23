#pragma once
#include <SFML/Graphics.hpp>
#include "World.h"

#define WIDTH 1000
#define HEIGHT 1000

#define TILEMAP_X 100
#define TILEMAP_Y 100
#define TILESIZE 32

class Game {
//VARS
private:
    World world;
    sf::View view;
    sf::RenderWindow window;
//FUNCTIONS
public:
    Game();
    ~Game();
    void run();
private:
    void update();
    void processEvents();
    void render();
};



