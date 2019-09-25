

#include "Game.h"

Game::Game(): world(sf::Vector2i(TILEMAP_X,TILEMAP_Y),TILESIZE) , window(sf::VideoMode(WIDTH,HEIGHT),"Automata")  {
    world.setdrawGrid(true);
    entMgr.setBoundaries(world);
    entMgr.spawnCreatures(100);
    view.setSize(sf::Vector2f(3000.0f,3000.0f));
    view.setCenter(WIDTH/2,HEIGHT/2);
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
    entMgr.Update();
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    window.close();
                    break;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    entMgr.spawnCreatures(100);
                    break;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
                    entMgr.spawnCreatures(1000);
                    break;
                }

            case sf::Event::Closed:
                window.close();
                break;
        }
    }
    sf::Vector2i position = sf::Mouse::getPosition(window);
    if(position.x<WIDTH*0.01)
    {
        view.move(-0.1f,0.0f);
    }
    else if(position.x>WIDTH-(0.01*WIDTH))
    {
        view.move(0.1f,0.0f);
    }

    else if(position.y<HEIGHT*0.01)
    {
        view.move(0.0f,-0.1f);
    }
    else if(position.y>HEIGHT-(0.01*HEIGHT))
    {
        view.move(0.0f,0.1f);
    }



}

void Game::render() {
    window.clear(sf::Color(50,50,50));
    window.setView(view);
    world.Draw(window);
    entMgr.Draw(window);
    window.display();
}
