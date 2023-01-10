#include "../include/king.h"

const int King::HEALTH = 500;

King::King(std::shared_ptr<Layout> layout, std::shared_ptr<sf::RenderWindow> window) : Moveable(15, 15, 2, layout, window){
    
    healthBar = std::make_unique<ProgressBar>(x, y - 10, HEALTH, HEALTH, window);

    image.setSmooth(true);
    if(image.loadFromFile("resources/king.png")) {
        // printf("load king image success\n");
    } else {
        printf("error: load king image fail\n");
    }
    king.setTexture(image);
    // king.setPosition(310.f, 310.f);
    king.setScale(30.f / image.getSize().x, 30.f/image.getSize().y);
    draw();

    end.setString("Game Over!");
    end.setFillColor(sf::Color::Red);
    end.setCharacterSize(48);
    end.setFont(*font);
    end.setPosition(sf::Vector2f(400, 300));
    isDead = false;
}

void King::takeDamage(int damage) {
    if(!healthBar->decreaseBar(damage)) {
        printf("you died!\n");
        window->draw(end);
        isDead = true;
    }
}

bool King::getIsDead() {
    return isDead;
}

void King::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        moveLeft();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        moveRight();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        moveUp();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        moveDown();
    } else {
        stationary();

    }

    Moveable::update();
    healthBar->updatePosition(x, y - 10);
    healthBar->update();
}

void King::draw() {
    king.setPosition((float)(x - 5), (float)(y - 10));
    window->draw(king);
    healthBar->draw();

    if(isDead) {
        window->draw(end);
    }
}

int King::getGridX() {
    return gridX;
}

int King::getGridY() {
    return gridY;
}

King::~King() {}