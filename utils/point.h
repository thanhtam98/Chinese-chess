#ifndef __POINT_H__
#define __POINT_H__
#include "utils/constant.h"

class Point {
public:
    Point *of(int _x, int _y);
    team_code getTeam();
private:
    Point(int _x, int _y): x(_x), y(_y) {};
    int x;
    int y;
    Point* cache[BOARD_LENGTH*BOARD_WIDTH];
};

#endif
