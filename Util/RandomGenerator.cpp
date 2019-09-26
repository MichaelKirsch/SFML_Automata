#include "RandomGenerator.h"
int custom_random_generator::getRandomInt(int min, int max){
     return min + rand() % (( max + 1 ) - min);
}
void custom_random_generator::reseed(){
    srand(time(NULL));
}

sf::Vector3i custom_random_generator::getRandomColor() {
    return sf::Vector3i(getRandomInt(0,255),getRandomInt(0,255),getRandomInt(0,255));
}

sf::Vector2i custom_random_generator::getRandomPosition(int minx, int maxx, int miny, int maxy) {
    return sf::Vector2i(getRandomInt(minx,maxx),getRandomInt(miny,maxy));
}


