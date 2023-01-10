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
    switch (dir)
    {
    case WEST:
        return x-1 >= 0;
    case EAST:
        return x+1 < BOARD_WIDTH;
    case NORTH:
        return y+1 < BOARD_LENGTH;
    case SOUTH:
        return y-1 >= 0;
    case NORTH_WEST:
        return y+1 < BOARD_LENGTH && x-1 >= 0;
    case NORTH_EAST:
        return y+1 < BOARD_LENGTH && x+1 < BOARD_WIDTH;
    case SOUTH_WEST:
        return y-1 >= 0 && x-1 >= 0;
    case SOUTH_EAST:
        return y-1 >= 0 && x+1 < BOARD_WIDTH;
    default:
        std::cout << "Throw exception " << std::endl;
        return false;
    }
}

Point *DirectionInterator::getNext(){
    switch (dir)
    {
    case WEST:
        // std::cout << "*[" << x - 1<< "," << y << "]" << std::endl;
        return Point::of(--x, y);
    case EAST:
        // std::cout << "*[" << x + 1<< "," << y << "]" << std::endl;
        return Point::of(++x, y);
    case NORTH:
        // std::cout << "*[" << x  << "," << y + 1 << "]" << std::endl;
        return Point::of(x, ++y);
    case SOUTH:
        // std::cout << "*[" << x << "," << y - 1<< "]" << std::endl;
        return Point::of(x, --y);
    case NORTH_WEST:
        // std::cout << "*[" << x - 1<< "," << y +1 << "]" << std::endl;
        return Point::of(--x, ++y);
    case NORTH_EAST:
        // std::cout << "*[" << x + 1<< "," << y +1<< "]" << std::endl;
        return Point::of(++x, ++y);
    case SOUTH_WEST:
        // std::cout << "*[" << x - 1<< "," << y -1 << "]" << std::endl;
        return Point::of(--x, --y);
    case SOUTH_EAST:
        // std::cout << "*[" << x + 1<< "," << y -1 << "]" << std::endl;
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

