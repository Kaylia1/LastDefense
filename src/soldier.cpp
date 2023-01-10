#include "../include/soldier.h"


const int Soldier::ATTACK = 10;
const int Soldier::COST = 100;
const double Soldier::TIMER = 15.0; //seconds
int Soldier::damage[31][31];

Soldier::Soldier(int x, int y, std::shared_ptr<Layout> layout, std::shared_ptr<sf::RenderWindow> window) : Element(window){
    this->x = x;
    this->y = y;
    this->layout = layout;
    nextSoldier = nullptr;
    lastSoldier = nullptr;
    toDelete = false;

    image.setSmooth(true);
    if(!image.loadFromFile("resources/knight.png")) {
        printf("error: load knight image fail\n");
    }
    soldier.setTexture(image);
    soldier.setScale(35.f / image.getSize().x, 35.f/image.getSize().y);

    startTime = std::chrono::steady_clock::now();
    timer = std::make_unique<ProgressBar>(x*20, y*20, TIMER, TIMER, window);
    timer->setColor(sf::Color::Blue);
}

void Soldier::setNextSoldier(std::shared_ptr<Soldier> next){
    nextSoldier = next;
}
void Soldier::setLastSoldier(std::shared_ptr<Soldier> last){
    lastSoldier = last;
}

std::shared_ptr<Soldier> Soldier::getNextSoldier() {
    return nextSoldier;
}

void Soldier::initDamageMap() {
    for(int i = 0; i < 31; i++) {
        memset(Soldier::damage[i], 0, 31*sizeof(int));
    }
}

int Soldier::getDamage(int x, int y) {
    return damage[x][y];
}

int Soldier::getX() {
    return x;
}

int Soldier::getY() {
    return y;
}

void Soldier::update() {
    auto curTime = std::chrono::steady_clock::now();

    Soldier::damage[x][y] += ATTACK;
    Soldier::damage[x - 1][y] += ATTACK;
    Soldier::damage[x + 1][y] += ATTACK;
    Soldier::damage[x][y - 1] += ATTACK;
    Soldier::damage[x][y + 1] += ATTACK;

    if(nextSoldier != nullptr) {
        nextSoldier->update();
    }

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(curTime - startTime);
    if(!timer->setBar(TIMER - duration.count() / 1000.0)) { //soldier timed out
        die();
    }
    timer->update();
}

void Soldier::draw() {
    // printf("ATTEMPTING TO DRAW\n");
    soldier.setPosition((float)(x*20 - 5), (float)(y*20 - 5));
    window->draw(soldier);
    timer->draw();
    if(nextSoldier != nullptr) {
        nextSoldier->draw();
    }
}

void Soldier::die() {
    // printf("dead\n");
    toDelete = true;
    if(lastSoldier != nullptr) { // soldierManager handles root cases
        layout->removeBlockade(x, y);
        lastSoldier->setNextSoldier(nextSoldier);
    }
}

bool Soldier::getToDelete() {
    return toDelete;
}

Soldier::~Soldier(){}