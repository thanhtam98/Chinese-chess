#include "utils/utils.h"
#include<bits/stdc++.h>

void Utils::removePointFromVector(std::vector<Point*> *pointVector, int x, int y){
    if (Point::isWithinBoundary(x,y))
    {
        Point *point = Point::of(x,y);
        // cout << "Point [" << point->getX() << "," << point->getY() << "]:" << endl;
        // std::remove(pointVector->begin(),pointVector->end(),point);
        pointVector->erase(find(pointVector->begin(),pointVector->end(),point));

    }
}
bool Utils::isDirContainsInList(std::vector<direction_code> list, direction_code dir)
{
    return std::find(list.begin(), list.end(), dir) != list.end();
}