#include "../../include/utility/element.h"

sf::Font* Element::font = nullptr; //remember to call initFonts()

Element::Element(std::shared_ptr<sf::RenderWindow> window) {
    this->window = window;
}

void Element::initFonts() {
    font = new sf::Font();
    if(!font->loadFromFile("Sansation-Regular.ttf")) {
        printf("ERROR failed to load font\n");
    }
}
