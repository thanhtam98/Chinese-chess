#include "utils/point.h"
#include <iostream>

Point* Point::cache[BOARD_LENGTH*BOARD_WIDTH] = {};
// Point** Point::cache = Point::alloc_cache();
Point* Point::of(int _x, int _y) {
    if (!isWithinBoundary(_x, _y))
        throw std::invalid_argument("Class Point: Invalid Coordinate");
    int index =  _y * BOARD_WIDTH + _x;
    if (cache[index] == nullptr) {
        return cache[index] = new Point(_x, _y);
    }
    return cache[index];
}

bool Point::isWithinBoundary(int x, int y) {
    return !(x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_LENGTH);
}

// Point** Point::alloc_cache(){
//     int size = BOARD_LENGTH*BOARD_WIDTH;
//     Point **p = new Point*[size];
//     for (int i = 0; i < size; i++)
//         p[i] = nullptr;
//     return p;
// }
team_code Point::getTeam() {
    return y >  FRONTIER ?  RED : BLACK;
}
int Point::getX(){
    return x;
}
int Point::getY(){
    return y;
}