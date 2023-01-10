#ifndef MOVEABLE
#define MOVEABLE

#include <math.h>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "utility/element.h"
#include "layout.h"

/**
 * Elements which can move between grid squares with the same animated movements.
*/
class Moveable : public Element {
    public:
        enum Direction {
            up,
            down,
            left,
            right,
            none
        };

        Moveable(int x, int y, int speed, std::shared_ptr<Layout> layout, std::shared_ptr<sf::RenderWindow> window);

        virtual void update();
        virtual void draw() = 0;

        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void stationary();

        bool isStationary();

        ~Moveable();

    protected:
        int x;
        int y;
        int speed;

        int gridX;
        int gridY;

        Direction curDir;
        Direction nextDir;
        std::shared_ptr<Layout> layout;

};

#endif