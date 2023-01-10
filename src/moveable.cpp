#include "../include/moveable.h"

/**
 * @param x grid x
 * @param y grid y
 * @param speed speed in pixels moved per loop
*/
Moveable::Moveable(int x, int y, int speed, std::shared_ptr<Layout> layout, std::shared_ptr<sf::RenderWindow> window) : Element(window){
    nextDir = none;
    curDir = none;
    gridX = x;
    gridY = y;
    this->x = gridX * 20;
    this->y = gridY * 20;
    this->speed = speed;

    this->layout = layout;
}

void Moveable::update() {
    if(isStationary()) {
        curDir = nextDir;
        nextDir = none;
    }

    switch(curDir) {
        case up:
            if(abs(y - (gridY - 1) * 20) < abs(y - speed - (gridY - 1) * 20)) { //cur distance < projected distance to target
                curDir = none;
                nextDir = none;
                gridY--;
                y = gridY * 20;
            } else {
                y -= speed;
            }
            break;
        case down:
            if(abs(y - (gridY + 1) * 20) < abs(y + speed - (gridY + 1) * 20)) { //cur distance < projected distance
                curDir = none;
                nextDir = none;
                gridY++;
                y = gridY * 20;
            } else {
                y += speed;
            }
            break;
        case right:
            if(abs(x - (gridX + 1) * 20) < abs(x + speed - (gridX + 1) * 20)) { //cur distance < projected distance
                curDir = none;
                nextDir = none;
                gridX++;
                x = gridX * 20;
            } else {
                x += speed;
            }
            break;
        case left:
            if(abs(x - (gridX - 1) * 20) < abs(x - speed - (gridX - 1) * 20)) { //cur distance < projected distance
                curDir = none;
                nextDir = none;
                gridX--;
                x = gridX * 20;
            } else {
                x -= speed;
            }
            break;
        case none:
            break;
    }
}

bool Moveable::isStationary() {
    return curDir == none;
}

void Moveable::moveUp() {
    if(!layout->collides(gridX, gridY - 1))
        nextDir = up;
}

void Moveable::moveDown() {
    if(!layout->collides(gridX, gridY + 1))
        nextDir = down;
}

void Moveable::moveLeft() {
    if(!layout->collides(gridX - 1, gridY))
        nextDir = left;
}

void Moveable::moveRight() {
    if(!layout->collides(gridX + 1, gridY))
        nextDir = right;
}

void Moveable::stationary() {
    nextDir = none;
}

Moveable::~Moveable() {}