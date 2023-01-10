#ifndef LAYOUT
#define LAYOUT

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "utility/element.h"

class Layout : public Element{
    public:
        Layout(std::shared_ptr<sf::RenderWindow> window);
        virtual void update();
        virtual void draw();
        bool collides(int x, int y);
        // bool binarySearch(int x, int y, int upper, int lower); //too inefficient, switch to map

        void addBlockade(int x, int y);
        void removeBlockade(int x, int y);

        ~Layout();


    private:
        int barriers[31][31]; //0 is walkable, 1 is barrier, 2 is soldier

        // void addBlockadeHelper(int x, int y, int upper, int lower);
        // void removeBlockadeHelper(int x, int y, int upper, int lower);
        sf::Texture layout;
        sf::Sprite background;
        // std::vector<int*> barriers; //vector of coords, too inefficient

};

#endif