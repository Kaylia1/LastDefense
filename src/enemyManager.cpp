#include "../include/enemyManager.h"

const int EnemyManager::SPAWN_LOCATIONS[4][2] = {{0, 15}, {15, 0}, {15, 30}, {30, 15}};

EnemyManager::EnemyManager(std::shared_ptr<King> king, std::shared_ptr<Layout> layout, std::shared_ptr<sf::RenderWindow> window) : Element(window){
    
    this->king = king;
    this->layout = layout;
    root = nullptr;
    
    srand((unsigned) time(NULL)); //random seed via time
}

void EnemyManager::update() {
    if(root != nullptr && root->getDeletable()) {
        root = root->getNextEnemy(); //could be nullptr
    }

    int random = rand() % 1000; //random number 0-500
    if(root == nullptr || (root->getNextEnemy() == nullptr && random < 2) || random < 1) { //.2% chance of generating enemy if 1 enemy present, else .1% chance of generating enemy, insert at head of list
        int randPos = rand() % 4;
        std::shared_ptr<Enemy> newEnemy =
            std::make_shared<Enemy>(SPAWN_LOCATIONS[randPos][0], SPAWN_LOCATIONS[randPos][1], king, layout, window);
       
        if(root == nullptr) {
            root = newEnemy; //last and next are nullptr
        } else {
            newEnemy->setNextEnemy(root);
            root->setLastEnemy(newEnemy);
            root = newEnemy; 
        }
    }

    if(root != nullptr) { //updating from the most recently generated enemy to oldest enemy
        root->update();
    }
}

void EnemyManager::draw() {
    if(root != nullptr) {
        root->draw();
    }
}
        
EnemyManager::~EnemyManager(){}