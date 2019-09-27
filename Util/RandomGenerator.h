#pragma once
#include <iostream>
#include <random>
#include <time.h>
#include "SFML/Graphics.hpp"

namespace custom_random_generator
{
    int getRandomInt(int min,int max);
    sf::Vector3i getRandomColor();
    sf::Vector2i generateMovePos(sf::Vector2i oldPosition);
    sf::Vector2i getRandomPosition(int minx,int maxx,int miny,int maxy);
    int getMutation();
    void reseed();
}




