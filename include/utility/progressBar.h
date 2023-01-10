#ifndef PROGRESS_BAR
#define PROGRESS_BAR

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "element.h"

class ProgressBar : public Element {

    public:

        static const int WIDTH;
        static const int HEIGHT;

        ProgressBar(int x, int y, int total, int starter, std::shared_ptr<sf::RenderWindow> window);

        void update();
        void draw();

        void updatePosition(int x, int y);

        //returns false if amountProgressed becomes 0 or less
        bool decreaseBar(int amount);
        bool setBar(int amount);

        void setColor(sf::Color color);

        ~ProgressBar();

    private:
        int x, y;

        int amountTotal, amountProgressed;

        sf::RectangleShape bar;
        sf::RectangleShape current;
};

#endif