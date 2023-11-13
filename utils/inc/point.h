#ifndef __POINT_H__
#define __POINT_H__
#include "utils.h"
#include "constant.h"

#include <string>

class Point {
public:
    static Point *of(int _x, int _y);
    // static Point** alloc_cache();
    team_code getTeam();
    team_code getOpponentTeam();
    int getX();
    int getY();
    static bool isWithinBoundary(int x, int y);
    bool isWithinBoundary();
    bool isWithinPalace();
    std::string to_string();
private:
    // Point() {};
    Point(int _x, int _y): x(_x), y(_y) {};
    const int x;
    const int y;
    static Point *cache[BOARD_LENGTH*BOARD_WIDTH];
    friend std::ostream& operator<<(std::ostream &os,  Point &obj);
    // static Point **cache;
    
};

#endif
