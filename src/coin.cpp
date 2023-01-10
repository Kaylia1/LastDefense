#include "../include/coin.h"

int Coin::totalCurrency = 0;

Coin::Coin(int x, int y, std::shared_ptr<King> king, std::shared_ptr<sf::RenderWindow> window) : Element(window) {
    worth = 50;
    this->x = x;
    this->y = y;
    this->king = king;

    image.setSmooth(true);
    if(!image.loadFromFile("resources/money.png")) {
        printf("error: load money image fail\n");
    }
    money.setTexture(image);
    money.setScale(30.f / image.getSize().x, 30.f/image.getSize().y);

    consumed = false;
}

void Coin::update() {
    if(!consumed && king->getGridX() == x && king->getGridY() == y) {
        totalCurrency += 50;
        consumed = true;
        // printf("consumed!\n");
    }
}

void Coin::draw() {
    if(!consumed) {
        money.setPosition((float)(x*20), (float)(y*20));
        window->draw(money);
    }
}

int Coin::getCurrency() {
    return totalCurrency;
}

void Coin::spendCurrency(int amount) {
    totalCurrency -= amount;
}

bool Coin::getConsumed() {
    return consumed;
}

Coin::~Coin(){}