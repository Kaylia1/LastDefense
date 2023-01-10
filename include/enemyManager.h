#ifndef ENEMY_MANAGER
#define ENEMY_MANAGER

#include <memory>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "utility/element.h"
#include "enemy.h"

/**
 * Manages Enemy objects, creating them randomly at spawnpoints, updating them,
 * drawing them, and deleting the root enemy if it dies.
*/
class EnemyManager : public Element {
    public:
        static const int SPAWN_LOCATIONS[4][2];

        EnemyManager(std::shared_ptr<King> king, std::shared_ptr<Layout> layout, std::shared_ptr<sf::RenderWindow> window);

        virtual void update();
        virtual void draw();

        ~EnemyManager();
    private:
        std::shared_ptr<King> king;
        std::shared_ptr<Layout> layout;
        std::shared_ptr<Enemy> root;
};

#endif