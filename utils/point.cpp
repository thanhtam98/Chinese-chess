#include "utils/point.h"

Point* Point::of(int _x, int _y) {
    int index = _x * BOARD_WIDTH + _y;
    if (cache[index] == nullptr) {
        return cache[index] = new Point(_x, _y);
    }
    return cache[index];
}

team_code Point::getTeam(){
    return y >  FRONTIER ?  RED : BLACK;
}