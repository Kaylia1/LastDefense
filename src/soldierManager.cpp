#include "../include/soldierManager.h"

int SoldierManager::totalSoldierSummons = 0;

SoldierManager::SoldierManager(std::shared_ptr<King> king, std::shared_ptr<Layout> layout, std::shared_ptr<sf::RenderWindow> window) : Element(window) {
    this->king = king;
    this->layout = layout;
    notEnoughText.setString("Not enough money!");
    notEnoughText.setFillColor(sf::Color::Red);
    notEnoughText.setCharacterSize(20);
    notEnoughText.setFont(*font);

    summons.setString("Soldiers Summoned:");
    summons.setFillColor(sf::Color::Black);
    summons.setCharacterSize(14);
    summons.setFont(*font);
    summons.setPosition(sf::Vector2f(630, 100));
    startValid = false;
}

void SoldierManager::draw() {
    // printf("draw updating\n");
    if(root != nullptr) {
        root->draw();
    }
    if(startValid) {
        window->draw(notEnoughText);
        auto curTime = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(curTime - startTime);
        if(duration.count() / 1000.0 > 0.5) {
            startValid = false;
        }
    }

    std::stringstream ss;
    ss << "Soldiers Summoned:";
    ss << totalSoldierSummons;
    summons.setString(ss.str());
    window->draw(summons);
}

void SoldierManager::update() {
    Soldier::initDamageMap(); //zero damages

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){ //create soldier at king location
        addSoldier(king->getGridX(), king->getGridY());
    } else if(root != nullptr && root->getToDelete()) { //can't create and delete at same time
        layout->removeBlockade(root->getX(), root->getY());
        root = root->getNextSoldier();
        // printf("deleting root soldier");
    }

    //update soldiers
    if(root != nullptr) {
        root->update();
    }
}

void SoldierManager::addSoldier(int x, int y) {
    if(Coin::getCurrency() < Soldier::COST) { //check can afford
        if(!layout->collides(x, y)){ //didn't already put one down here
            //show not enough money text
            notEnoughText.setPosition(sf::Vector2f(float(x*20) - 50, float(y*20)));
            startTime = std::chrono::steady_clock::now();
            startValid = true;
        }
        return;
    }
    totalSoldierSummons++;
    Coin::spendCurrency(Soldier::COST);
    std::shared_ptr<Soldier> newSoldier = std::make_shared<Soldier>(x, y, layout, window);
    if(root == nullptr) {
        root = newSoldier;
    } else {
        newSoldier->setNextSoldier(root);
        root->setLastSoldier(newSoldier);
        root = newSoldier;
    }
    layout->addBlockade(x, y);
}

SoldierManager::~SoldierManager(){}