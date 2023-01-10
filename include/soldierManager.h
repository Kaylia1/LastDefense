#ifndef SOLDIER_MANAGER
#define SOLDIER_MANAGER

#include <memory>
#include <ctime>
#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "layout.h"
#include "soldier.h"
#include "utility/element.h"
#include "coin.h"

/**
 * Manages soldiers by updating, drawing, and creating them.
*/
class SoldierManager : public Element {
    public:

        static int totalSoldierSummons;

        SoldierManager(std::shared_ptr<King> king, std::shared_ptr<Layout> layout, std::shared_ptr<sf::RenderWindow> window);
        virtual void draw();
        virtual void update();
        void addSoldier(int x, int y);
        ~SoldierManager();

    private:
        std::shared_ptr<King> king;
        std::shared_ptr<Layout> layout;
        std::shared_ptr<Soldier> root;


        sf::Text notEnoughText, summons;
        std::chrono::steady_clock::time_point startTime;
        bool startValid;
};

#endif