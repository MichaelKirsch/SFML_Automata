#include "RandomGenerator.h"
int custom_random_generator::getRandomInt(int min, int max){
     return min + rand() % (( max + 1 ) - min);
}
void custom_random_generator::reseed(){
    srand(time(NULL));
}


