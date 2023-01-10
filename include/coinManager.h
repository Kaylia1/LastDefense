#ifndef COIN_MANAGER
#define COIN_MANAGER

#include <memory>
#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "utility/element.h"
#include "king.h"
#include "coin.h"
#include "layout.h"

/**
 * Manages coins in a simple array, limits the game to 5 collectable
 * cash pieces at a time. Cash cannot spawn inside barriers, but that can
 * spawn on enemy spawnpoints, be careful!
*/
class CoinManager : public Element {
    public:
        CoinManager(std::shared_ptr<King> king, std::shared_ptr<Layout> layout, std::shared_ptr<sf::RenderWindow> window);
        void update();
        void draw();
        ~CoinManager();
    private:
        std::shared_ptr<King> king;
        std::unique_ptr<Coin> coins[5]; //max 5 coins

        std::shared_ptr<Layout> layout;

        sf::Text text;
};

#endif