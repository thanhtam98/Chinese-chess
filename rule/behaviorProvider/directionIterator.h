#pragma once
#include "utils/point.h"
#include "utils/constant.h"


class DirectionInterator {

public:
        DirectionInterator(Point *point, direction_code dir);
        bool hasNext();
        Point* getNext();
        void changeDir(direction_code dir); 
private:
        int x,y;
        Point* target;
        direction_code dir;
        void reset(void);
};