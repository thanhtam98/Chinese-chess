#include "utils/point.h"
#include <iostream>

Point* Point::cache[BOARD_LENGTH*BOARD_WIDTH] = {};
// Point* Point::cache[BOARD_LENGTH*BOARD_WIDTH] = Point::alloc_cache();
Point* Point::of(int _x, int _y) {
    int index = _x * BOARD_WIDTH + _y;
    if (cache[index] == nullptr) {
        std::cout << "Assign a new Point a(" << _x << ", " << _y << ");" << endl;
        return cache[index] = new Point(_x, _y);
    }
    return cache[index];
}

// Point** Point::alloc_cache(){
//     int size = BOARD_LENGTH*BOARD_WIDTH;
//     Point **p = new Point**();
//     for (int i = 0; i < size; i++)
//         p[i] = new Point*();
//     return p;
// }
team_code Point::getTeam() {
    return y >  FRONTIER ?  RED : BLACK;
}