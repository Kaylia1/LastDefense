#include "../include/layout.h"

Layout::Layout(std::shared_ptr<sf::RenderWindow> window) : Element(window){
    
    if(layout.loadFromFile("resources/backdrop.png")) {
        // printf("load background image success\n");
    } else {
        printf("error: load background image fail\n");
    }
    
    background.setTexture(layout);
    background.setPosition(0, 0);
    background.setScale(620.f / layout.getSize().x, 620.f/layout.getSize().y);
}

//find all barriers, sorted by low x then low y
void Layout::update() {
    for(int i = 0; i <= 30; i++) {
        for(int j = 0; j <= 30; j++) {
            if(window->capture().getPixel(i*20 + 10, j*20 + 10) == sf::Color::Black) {
                barriers[i][j] = 1;
                // int * point = new int[2];
                // point[0] = i;
                // point[1] = j;
                // barriers.push_back(point);
            } else {
                barriers[i][j] = 0;
            }
        }
    }
}

bool Layout::collides(int x, int y) {
    if(x > 30 || x < 0 || y < 0 || y > 30) return true;
    return barriers[x][y] > 0;
    //binary search
    // return binarySearch(x, y, barriers.size() - 1, 0);
}

// bool Layout::binarySearch(int x, int y, int upper, int lower) {
//     if(upper < lower) {
//         return false;
//     }
//     int i = (upper + lower) / 2;
//     if(barriers[i][0] == x && barriers[i][1] == y) { //found
//         return true;
//     } else if (barriers[i][0] == x && barriers[i][1] > y ||
//         barriers[i][0] > x) { //go left
//         return binarySearch(x, y, i - 1, lower);

//     // } else if (barriers[i][0] == x && barriers[i][1] < y ||
//         // barriers[i][0] < x){ //go right
//     } else {
//         return binarySearch(x, y, upper, lower + 1);
//     }
// }

void Layout::addBlockade(int x, int y) {
    barriers[x][y] = 2;
    // addBlockadeHelper(x, y, barriers.size() - 1, 0);
}

// void Layout::addBlockadeHelper(int x, int y, int upper, int lower) {
//     if(upper < lower) {
//         int * newPoint = new int[2];
//         newPoint[0] = x;
//         newPoint[1] = y;
//         barriers.insert(barriers.begin() + lower, newPoint);
//         return;
//     }
//     int i = (upper + lower) / 2;
//     if(barriers[i][0] == x && barriers[i][1] == y) { //something already here, possible warning?
//         return;
//     } else if (barriers[i][0] == x && barriers[i][1] > y ||
//         barriers[i][0] > x) { //go left
//         addBlockadeHelper(x, y, i - 1, lower);
//     } else {
//         addBlockadeHelper(x, y, upper, lower + 1);
//     }
// }

void Layout::removeBlockade(int x, int y) {
    barriers[x][y] = 0;
    // removeBlockadeHelper(x, y, barriers.size() - 1, 0);
}

// void Layout::removeBlockadeHelper(int x, int y, int upper, int lower) {
//     if(upper < lower) {
//         return; //not found, nothing to remove
//     }
//     int i = (upper + lower) / 2;
//     if(barriers[i][0] == x && barriers[i][1] == y) { //found
//         delete barriers[i];
//         barriers.erase(barriers.begin() + i); //remove index i
//     } else if (barriers[i][0] == x && barriers[i][1] > y ||
//         barriers[i][0] > x) { //go left
//         removeBlockadeHelper(x, y, i - 1, lower);
//     } else {
//         removeBlockadeHelper(x, y, upper, lower + 1);
//     }
// }

void Layout::draw() {
    window->draw(background);
}

Layout::~Layout(){
    // for(int i = 0; i < barriers.size(); i++) {
    //     delete barriers[i];
    // }
}