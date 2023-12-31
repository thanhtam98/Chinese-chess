#include "utils.h"
#include <iostream>
#include <bits/stdc++.h> 

Point* Point::cache[BOARD_LENGTH*BOARD_WIDTH] = {};
// Point** Point::cache = Point::alloc_cache();
Point* Point::of(int _x, int _y) {
    if (!isWithinBoundary(_x, _y)) {
        std::cout << "x: " << _x << "; y: " << _y << std::endl;
        throw std::invalid_argument("Class Point: Invalid Coordinate");
    }
    int index =  _y * BOARD_WIDTH + _x;
    if (cache[index] == nullptr) {
        return cache[index] = new Point(_x, _y);
    }
    return cache[index];
}

bool Point::isWithinBoundary(int x, int y) {
    return !(x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_LENGTH);
}

bool Point::isWithinBoundary() {
    return !(x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_LENGTH);
}

bool Point::isWithinPalace() {
    return (x >= 3 && x <= 5) && ((y >= 0 && y <= 2)||(y >= 7 && y <= 9));
}

// Point** Point::alloc_cache(){
//     int size = BOARD_LENGTH*BOARD_WIDTH;
//     Point **p = new Point*[size];
//     for (int i = 0; i < size; i++)
//         p[i] = nullptr;
//     return p;
// }
team_code Point::getTeam() {
    return y >  FRONTIER ?  BLACK : RED;
}
team_code Point::getOpponentTeam(){
    return getTeam() == BLACK ? RED : BLACK;
}
int Point::getX(){
    return x;
}
int Point::getY(){
    return y;
}

std::ostream& operator<<(std::ostream &os,  Point &obj)
{
    os << "[" << obj.getX() << ","
                   << obj.getY() << "]";
    os << endl;
    return os;
}

std::string Point::to_string() {
    char buff[10];
    sprintf(buff, "[%d:%d]", x, y);
    return string(buff);
}