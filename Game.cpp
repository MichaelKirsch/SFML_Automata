

#include "Game.h"

Game::Game() : world(sf::Vector2i(100,100), true,32) , window(sf::VideoMode(WIDTH,HEIGHT),"Automata")  {
}

Game::~Game() {

}

void Game::run() {
    while(window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::update() {

}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
        }
    }
}

void Game::render() {
    window.clear(sf::Color(50,50,50));
    world.Draw(window);
    window.display();
}
