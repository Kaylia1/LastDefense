
#include "../include/coinManager.h"

CoinManager::CoinManager(std::shared_ptr<King> king, std::shared_ptr<Layout> layout, std::shared_ptr<sf::RenderWindow> window) : Element(window) {
    
    for(int i = 0; i < 5; i++) {
        coins[i] = nullptr;
    }
    this->king = king;
    this->layout = layout;

    text.setString("$");
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(48);
    text.setFont(*font);
    // minX = x - text->getLocalBounds().width / 2;
    // minY = y - text->getLocalBounds().height;
    text.setPosition(sf::Vector2f(630, 50));
}

void CoinManager::update() {
    int random = rand(); //random number 0-500
    int index = random % 5;
    random = rand();
    int x = random % 31;
    random = rand();
    int y = random % 31;

    if((coins[index] == nullptr || coins[index]->getConsumed()) && !layout->collides(x, y)) { //overwrite new coin
        coins[index] = std::make_unique<Coin>(x, y, king, window);
    }
    for(int i = 0; i < 5; i++) {
        if(coins[i] != nullptr)
            coins[i]->update();
    }
    std::stringstream ss;
    ss << "$";
    ss << Coin::getCurrency();
    text.setString(ss.str());
}

void CoinManager::draw() {
    for(int i = 0; i < 5; i++) {
        if(coins[i] != nullptr)
            coins[i]->draw();
    }
    window->draw(text);
}

CoinManager::~CoinManager(){}