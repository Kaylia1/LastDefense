#ifndef ENEMY
#define ENEMY

#include <memory>
#include <queue>
#include <math.h>
#include <cstring>
#include <iostream>
#include <ctime>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "moveable.h"
#include "king.h"
#include "soldier.h"

#include "utility/progressBar.h"

/**
 * An explosive enemy that does damage to the King when contacting him. Takes
 * damage from nearby soldiers. Pathfinds to king via Depth-First-Search, as there
 * are no weighted edges and the layout of barriers is odd enough for inefficient
 * heurestics (for a*).
*/
class Enemy : public Moveable {
    public:

        static const sf::Color COLOR;
        static const sf::Color OUTLINE_COLOR;
        static const int ATTACK;
        static const int HEALTH;

        struct PotentialPos {
            PotentialPos(int newX, int newY, Direction dir) : x(newX), y(newY), initDir(dir){}
            int x, y;
            Direction initDir;
        };

        Enemy(int x, int y, std::shared_ptr<King> king, std::shared_ptr<Layout> layout, std::shared_ptr<sf::RenderWindow> window);
        void update();
        void draw();

        void setLastEnemy(std::shared_ptr<Enemy> last);
        void setNextEnemy(std::shared_ptr<Enemy> next);
        bool getDeletable();
        std::shared_ptr<Enemy> getLastEnemy(); //unused
        std::shared_ptr<Enemy> getNextEnemy();
        ~Enemy();
    private:

        void die();

        Direction bfs(int kingX, int kingY);
        sf::CircleShape circle;
        std::shared_ptr<Enemy> nextEnemy, lastEnemy;
        std::shared_ptr<King> target;
        bool exploded;
        bool toDelete;

        std::unique_ptr<ProgressBar> healthBar;

        sf::Texture image;
        sf::Sprite explosion;

        std::chrono::steady_clock::time_point explosionStart;
        
};

#endif