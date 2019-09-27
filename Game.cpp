

#include "Game.h"

Game::Game(): world(sf::Vector2i(TILEMAP_X,TILEMAP_Y),TILESIZE) , window(sf::VideoMode(WIDTH,HEIGHT),"Automata")  {
    custom_random_generator::reseed();
    world.setdrawGrid(true);
    entMgr.attachtoWorld(world);
    entMgr.spawnCreatures(100);
    view.setSize(sf::Vector2f(4000.0f,4000.0f));
    view.setCenter(WIDTH/2,HEIGHT/2);
}

Game::~Game() {

}

void Game::run() {

    sf::Clock clock;
    while(window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        processEvents();
        update(elapsed);
        render();
    }
}

void Game::update(sf::Time elapsed) {
    time_passed+=elapsed.asSeconds();
    if(time_passed>0.05)
    {
        printf("Creatures:%i\n",entMgr.getNbrCreatures());
        time_passed=0.0;
        entMgr.Update();
    }

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
                    entMgr.spawnCreatures(1);
                    break;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
                    entMgr.spawnCreatures(10);
                    break;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
                    world.toggleGrid();
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
