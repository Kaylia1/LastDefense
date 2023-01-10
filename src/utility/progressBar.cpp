#include "../../include/utility/progressBar.h"

const int ProgressBar::WIDTH = 25;
const int ProgressBar::HEIGHT = 2;

ProgressBar::ProgressBar(int x, int y, int total, int starter, std::shared_ptr<sf::RenderWindow> window) :
    Element(window),
    bar(sf::Vector2f((float)x, (float)y)),
    current(sf::Vector2f((float)x, (float)y)) {

    bar.setSize(sf::Vector2f((float)WIDTH, (float)HEIGHT));
    current.setSize(sf::Vector2f((float)WIDTH, (float)HEIGHT));

    bar.setFillColor(sf::Color::Red);
    current.setFillColor(sf::Color::Green);
    this->x = x;
    this->y = y;

    amountTotal = total;
    amountProgressed = starter;
}

void ProgressBar::update() {
    current.setSize(sf::Vector2f((float)(WIDTH * amountProgressed / amountTotal), (float)HEIGHT));
}

void ProgressBar::updatePosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void ProgressBar::draw() {
    bar.setPosition(x - 2, y);
    current.setPosition(x - 2, y);
    window->draw(bar);
    window->draw(current);
}

bool ProgressBar::decreaseBar(int amount) {
    if(amountProgressed - amount < 0) {
        amountProgressed = 0;
        return false;
    } else {
        amountProgressed -= amount;
        return true;
    }
}

bool ProgressBar::setBar(int amount) {
    amountProgressed = amount;
    if(amountProgressed < 0) {
        amountProgressed = 0;
    } else if (amountProgressed > amountTotal) {
        amountProgressed = amountTotal;
    }
    return amountProgressed != 0;
}

void ProgressBar::setColor(sf::Color color) {
    current.setFillColor(color);
}

ProgressBar::~ProgressBar(){}