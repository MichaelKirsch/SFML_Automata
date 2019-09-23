#pragma once
#include <SFML/Graphics.hpp>
#include "World.h"

#define WIDTH 1000
#define HEIGHT 1000

class Game {
//VARS
private:
    World world;
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



