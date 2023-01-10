#ifndef ELEMENT
#define ELEMENT

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Element {
    public:
        Element(std::shared_ptr<sf::RenderWindow> window);
        virtual void update() = 0;
        virtual void draw() = 0;
        static void initFonts();
    protected:
        std::shared_ptr<sf::RenderWindow> window;
        static sf::Font* font;
};

#endif