#include <iostream>
#include "rule/ruleLimitBuilder.h"


// RuleLimitBuilder RuleLimitBuilder::limit()

RuleLimitBuilder RuleLimitBuilder::getValid()
{
    vector<Point*> *possibleMoves = &(rule.possibleMoves);
    Point* point = Point::of(0,3);
    // for (auto point : *possibleMoves)
    {
        if (rule.board->isOccupied(point)){
            std::cout << " Point: ["<<point->getX()<<","<<point->getY()<<"] is occupied! " << endl;
        } else{
            std::cout << " Point: ["<<point->getX()<<","<<point->getY()<<"] is not occupied! " << endl;
        }
    }
   
    return *this;
}