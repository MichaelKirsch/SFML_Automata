

#include "Game.h"

Game::Game() : world(sf::Vector2i(TILEMAP_X,TILEMAP_Y), true,TILESIZE) , window(sf::VideoMode(WIDTH,HEIGHT),"Automata")  {
    view.setSize(sf::Vector2f(5000.0f,5000.0f));
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
            case sf::Event::KeyPressed:
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    window.close();
                break;

            case sf::Event::Closed:
                window.close();
                break;
        }
    }
    sf::Vector2i position = sf::Mouse::getPosition(window);
    if(position.x<WIDTH*0.05)
    {
        view.move(-0.1f,0.0f);
    }
    else if(position.x>WIDTH-(0.05*WIDTH))
    {
        view.move(0.1f,0.0f);
    }

    else if(position.y<HEIGHT*0.05)
    {
        view.move(0.0f,-0.1f);
    }
    else if(position.y>HEIGHT-(0.05*HEIGHT))
    {
        view.move(0.0f,0.1f);
    }



}

void Game::render() {
    window.clear(sf::Color(50,50,50));
    window.setView(view);
    world.Draw(window);
    window.display();
}
