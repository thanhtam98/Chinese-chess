#ifndef __POINT_H__
#define __POINT_H__
#include "utils/constant.h"

class Point {
public:
    static Point *of(int _x, int _y);
    // static Point** alloc_cache();
    team_code getTeam();
private:
    Point() {};
    Point(int _x, int _y): x(_x), y(_y) {};
    int x;
    int y;
    static Point* cache[BOARD_LENGTH*BOARD_WIDTH];
};

#endif
