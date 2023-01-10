#ifndef SOLDIER
#define SOLDIER

#include <memory>
#include <ctime>
#include <math.h>
#include <cstring>
#include <chrono>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "layout.h"
#include "utility/progressBar.h"

/**
 * Attacks enemies within one horizontal or vertial square distance from them,
 * also acts as barriers which enemies but also the player cannot pass through.
 * Each soldier is only hired for a length of time.
*/
class Soldier : public Element {
    public:
        static const int ATTACK;
        static const int COST;
        static const double TIMER;

        Soldier(int x, int y, std::shared_ptr<Layout> layout, std::shared_ptr<sf::RenderWindow> window);
        virtual void update();
        virtual void draw();

        int getX();
        int getY();

        bool getToDelete();
        void setNextSoldier(std::shared_ptr<Soldier> next);
        void setLastSoldier(std::shared_ptr<Soldier> last);
        std::shared_ptr<Soldier> getNextSoldier();

        static void initDamageMap();
        static int getDamage(int x, int y);
        ~Soldier();
    private:
        void die();
        static int damage[31][31];

        int x, y; //grid coords
        std::chrono::steady_clock::time_point startTime;

        std::unique_ptr<ProgressBar> timer;
        bool toDelete;

        std::shared_ptr<Soldier> nextSoldier;
        std::shared_ptr<Soldier> lastSoldier;

        std::shared_ptr<Layout> layout;

        sf::Texture image;
        sf::Sprite soldier;


};

#endif