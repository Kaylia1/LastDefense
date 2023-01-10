#ifndef COIN
#define COIN

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "utility/element.h"
#include "king.h"

/**
 * Provides currency to the player when collected, which can
 * be used to temporarily hire soldiers to help the player defend
 * themselves.
*/
class Coin : Element {
    public:
        Coin(int x, int y, std::shared_ptr<King> king, std::shared_ptr<sf::RenderWindow> window);
        void update();
        void draw();
        bool getConsumed();
        static int getCurrency();
        static void spendCurrency(int amount);
        ~Coin();
    private:
        static int totalCurrency;

        int worth;
        int x, y; //grid coords
        bool consumed;
        std::shared_ptr<King> king;

        sf::Texture image;
        sf::Sprite money;
};

#endif