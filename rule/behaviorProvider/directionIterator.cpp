#include "rule/behaviorProvider/directionIterator.h"
#include <iostream>
DirectionInterator::DirectionInterator(Point *point, direction_code dir)
{
    target = point;
    this->dir = dir;
    x = point->getX();
    y = point->getY();
}

bool DirectionInterator:: hasNext(){
    return ((x-1 >= 0) && (x+1 <= BOARD_WIDTH) && (y-1 >= 0) && (y+1 <= BOARD_LENGTH));
}

Point *DirectionInterator::getNext(){
    switch (dir)
    {
    case WEST:
        return Point::of(--x, y);
    case EAST:
        return Point::of(++x, y);
    case NORTH:
        return Point::of(x, ++y);
    case SOUTH:
        return Point::of(x, --y);
    case NORTH_WEST:
        return Point::of(--x, ++y);
    case NORTH_EAST:
        return Point::of(++x, ++y);
    case SOUTH_WEST:
        return Point::of(--x, --y);
    case SOUTH_EAST:
        return Point::of(++x, --y);
    default:
        std::cout << "Throw exception " << std::endl;
        return nullptr;
    }
}

void DirectionInterator::changeDir(direction_code dir)
{
    this->dir= dir;
    reset();
}

void DirectionInterator:: reset ()
{
    x = target->getX();
    y = target->getY();
}

