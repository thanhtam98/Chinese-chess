#include <iostream>
#include "rule/ruleLimitBuilder.h"
#include "utils/utils.h"
// RuleLimitBuilder RuleLimitBuilder::limit()

RuleLimitBuilder RuleLimitBuilder::getValid()
{
    vector<Point *> *possibleMoves = &(rule.possibleMoves);
    Point *point = Point::of(0, 3);
    // for (auto point : *possibleMoves)
    {
        if (rule.board->isOccupied(0, 3))
        {
            std::cout << " Point: [" << point->getX() << "," << point->getY() << "] is occupied! " << endl;
        }
        else
        {
            std::cout << " Point: [" << point->getX() << "," << point->getY() << "] is not occupied! " << endl;
        }
    }

    return *this;
}
RuleLimitBuilder RuleLimitBuilder::excludeHobbling()
{
    Point *target = rule.target;
    int x = target->getX();
    int y = target->getY();
    vector<Point *> *possibleMoves = &(rule.possibleMoves);
    IBoard *board = rule.board;

    if (board->isOccupied(x + 1, y))
    {
        Utils::removePointFromVector(possibleMoves, x + 2, y + 1);
        Utils::removePointFromVector(possibleMoves, x + 2, y - 1);
    }
    if (board->isOccupied(x, y + 1))
    {
        Utils::removePointFromVector(possibleMoves, x - 1, y + 2);
        Utils::removePointFromVector(possibleMoves, x + 1, y + 2);
    }
    if (board->isOccupied(x - 1, y))
    {
        Utils::removePointFromVector(possibleMoves, x - 2, y + 1);
        Utils::removePointFromVector(possibleMoves, x - 2, y - 1);
    }
    if (board->isOccupied(x , y - 1))
    {
        Utils::removePointFromVector(possibleMoves, x - 1, y - 2);
        Utils::removePointFromVector(possibleMoves, x + 1, y - 2);
    }

    return *this;
}

RuleLimitBuilder RuleLimitBuilder::excludeChessmen(){
    Point *target = rule.target;
    vector<Point *> *possibleMoves = &(rule.possibleMoves);
    IBoard *board = rule.board;
    IChessman *targetChessmen = board->getChessman(target->getX(), target->getY());

    for (auto point : *possibleMoves)
    {
        int x = point->getX();
        int y = point->getY();

        IChessman *chessmen = board->getChessman(x,y);
        if (chessmen->getTeam() == targetChessmen->getTeam()){
            Utils::removePointFromVector(possibleMoves, x,y);
        }
    }
    return  *this;
}
