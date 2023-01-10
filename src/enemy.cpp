#include "../include/enemy.h"

const sf::Color Enemy::COLOR = sf::Color(255, 50, 50, 100);
const sf::Color Enemy::OUTLINE_COLOR = sf::Color(50, 10, 10);
const int Enemy::HEALTH = 1000;
const int Enemy::ATTACK = 100;

Enemy::Enemy(int x, int y, std::shared_ptr<King> king, std::shared_ptr<Layout> layout, std::shared_ptr<sf::RenderWindow> window) :
    Moveable(x, y, 1, layout, window),
    circle(5.f) { //10 pix radius

    circle.setFillColor(COLOR);
    circle.setOutlineThickness(2.f);
    circle.setOutlineColor(OUTLINE_COLOR);
    circle.setPosition((float)(gridX*20 + 5), (float)(gridY*20 + 5));

    healthBar = std::make_unique<ProgressBar>(gridX * 20 + 5, gridY * 20 + 5, HEALTH, HEALTH, window);

    target = king;
    nextEnemy = nullptr;
    lastEnemy = nullptr;

    //explosion graphics
    image.setSmooth(true);
    if(!image.loadFromFile("resources/explosion.png")) {
        printf("error: load explosion image fail\n");
    }
    explosion.setTexture(image);
    explosion.setScale(50.f / image.getSize().x, 50.f/image.getSize().y);
    exploded = false;
    toDelete = false;
}

void Enemy::die() {
    toDelete = true;
    if(lastEnemy != nullptr) { // enemyManager handles root cases
        lastEnemy->setNextEnemy(nextEnemy);
    }
}

void Enemy::update() {

    auto curTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(curTime - explosionStart);

    // check if exploded > 0.3s ago
    if(exploded && duration.count() / 1000.0 > 0.3) {  // explode for 0.3 seconds
        die();
        return;
    }
    
    //check if soldiers are damaging it
    int damageTaken = Soldier::getDamage(gridX, gridY);
    if(!healthBar->decreaseBar(damageTaken)) { // if died
        die();
        return;
    }


    // check if attacking king
    if(!exploded && gridX == target->getGridX() && gridY == target->getGridY()) {
        target->takeDamage(ATTACK);
        explosionStart = curTime;
        //like a bomb, implode
        exploded = true;
        return;
    }

    if(isStationary()) {
        /**
         * shortest path algorithm: dfs
         *      -no weighted edges so no need for djikstras,
         *      -barriers make it hard to get good heuristic for a*
         * */ 
        Direction dir = bfs(target->getGridX(), target->getGridY());
        switch(dir) {
            case up:
                moveUp();
                break;
            case down:
                moveDown();
                break;
            case left:
                moveLeft();
                break;
            case right:
                moveRight();
                break;
            case none:
                stationary();
                break;
        }
    } //else moving

    Moveable::update();
    healthBar->updatePosition(x, y);
    healthBar->update();
    if(nextEnemy != nullptr) {
        nextEnemy->update();
    }
}

bool Enemy::getDeletable() {
    return toDelete;
}

Moveable::Direction Enemy::bfs(int kingX, int kingY) {

    if(kingX == gridX && kingY == gridY) { //already attacking
        return none;
    }

    //init visited list
    bool visited[31][31];
    for(int i = 0; i < 31; i++) {
        memset(visited[i], 0, 31);
    }

    Direction findValid = none; //in case of interrupt
    std::queue<PotentialPos> q;
    visited[gridX][gridY] = true;

    if(!layout->collides(gridX - 1, gridY)) {
        q.push(PotentialPos(gridX - 1, gridY, left));
        visited[gridX - 1][gridY] = true;
        findValid = left;
    }
    if(!layout->collides(gridX + 1, gridY)) {
        q.push(PotentialPos(gridX + 1, gridY, right));
        visited[gridX + 1][gridY] = true;
        findValid = right;
    }
    if(!layout->collides(gridX, gridY - 1)) {
        q.push(PotentialPos(gridX, gridY - 1, up));
        visited[gridX][gridY - 1] = true;
        findValid = up;
    }
    if(!layout->collides(gridX, gridY + 1)) {
        q.push(PotentialPos(gridX, gridY + 1, down));
        visited[gridX][gridY + 1] = true;
        findValid = down;
    }

    while(!q.empty()) {
        PotentialPos latest = q.front(); //get next nearest node
        q.pop();

        if(latest.x == kingX && latest.y == kingY) { //found, send next position
            return latest.initDir;
        }

        //if not a wall, travel there
        if(!visited[latest.x - 1][latest.y] && !layout->collides(latest.x - 1, latest.y)) {
            q.push(PotentialPos(latest.x - 1, latest.y, latest.initDir));
            visited[latest.x - 1][latest.y] = true;
        }
        if(!visited[latest.x + 1][latest.y] && !layout->collides(latest.x + 1, latest.y)) {
            q.push(PotentialPos(latest.x + 1, latest.y, latest.initDir));
            visited[latest.x + 1][latest.y] = true;
        }
        if(!visited[latest.x][latest.y - 1] && !layout->collides(latest.x, latest.y - 1)) {
            q.push(PotentialPos(latest.x, latest.y - 1, latest.initDir));
            visited[latest.x][latest.y - 1] = true;
        }
        if(!visited[latest.x][latest.y + 1] && !layout->collides(latest.x, latest.y + 1)) {
            q.push(PotentialPos(latest.x, latest.y + 1, latest.initDir));
            visited[latest.x][latest.y + 1] = true;
        }
    }

    // king not found, due to recent map change
    // printf("error: king not found, impossible map?\n");
    return findValid; //keep moving randomly ig
}

void Enemy::draw() {
    circle.setPosition((float)(x + 5), (float)(y + 5));
    window->draw(circle);
    healthBar->draw();
    if(exploded) {
        explosion.setPosition((float)(x - 15), (float)(y - 10));
        window->draw(explosion);
    }

    if(nextEnemy != nullptr) {
        nextEnemy->draw();
    }
}
void Enemy::setNextEnemy(std::shared_ptr<Enemy> next) {
    nextEnemy = next;
}
void Enemy::setLastEnemy(std::shared_ptr<Enemy> last) {
    lastEnemy = last;
}

std::shared_ptr<Enemy> Enemy::getLastEnemy() {
    return lastEnemy;
}

std::shared_ptr<Enemy> Enemy::getNextEnemy() {
    return nextEnemy;
}

Enemy::~Enemy(){}