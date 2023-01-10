#include <iostream>
#include <stdio.h>
#include <memory>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "../include/king.h"
#include "../include/layout.h"
#include "../include/enemyManager.h"
#include "../include/coinManager.h"
#include "../include/soldierManager.h"

bool gameOngoing = true;

int main() {

    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(820, 620), "Last Defense");
    if(!window->isOpen()) {
        printf("error: failed to open window.");
    }
    window->setFramerateLimit(40);

    Element::initFonts();
    
    std::shared_ptr<Layout> layout = std::make_shared<Layout>(window);
    std::shared_ptr<King> king = std::make_shared<King>(layout, window);
    std::shared_ptr<EnemyManager> enemies = std::make_shared<EnemyManager>(king, layout, window);
    std::shared_ptr<CoinManager> coins = std::make_shared<CoinManager>(king, layout, window);
    std::shared_ptr<SoldierManager> soldiers = std::make_shared<SoldierManager>(king, layout, window);

    
    window->clear();
    layout->draw();
    window->display();
    layout->update(); //find barriers

    bool gameOn = true;

    while (window->isOpen())
    {
        if(gameOn) { //draw all elements
            window->clear(sf::Color(255, 240, 240));
            layout->draw();

            coins->draw();
            enemies->draw();
            soldiers->draw();
            king->draw();

            window->display();

            if(king->getIsDead()) {
                //game over
                gameOn = false;
            }
        }
        
        // sleep(0.5);
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        if(gameOn) { //update all elements
            king->update();
            soldiers->update();
            enemies->update();
            coins->update();
        }

    }

    return 0;
};