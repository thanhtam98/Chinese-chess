#include "utils/utils.h"
#include<bits/stdc++.h>

void Utils::removePointFromVector(std::vector<Point*> *pointVector, int x, int y){
    if (Point::isWithinBoundary(x,y))
    {
        Point *point = Point::of(x,y);
        std::remove(pointVector->begin(),pointVector->end(),point);
    }
}
