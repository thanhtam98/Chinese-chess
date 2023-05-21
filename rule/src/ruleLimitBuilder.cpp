#include <iostream>
#include "ruleLimitBuilder.h"
#include "utils.h"
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
    if (board->isOccupied(x, y - 1))
    {
        Utils::removePointFromVector(possibleMoves, x - 1, y - 2);
        Utils::removePointFromVector(possibleMoves, x + 1, y - 2);
    }

    return *this;
}

RuleLimitBuilder RuleLimitBuilder::excludeChessmen()
{
    Point *target = rule.target;
    vector<Point *> *possibleMoves = &(rule.possibleMoves);
    IBoard *board = rule.board;
    IChessman *targetChessmen = board->getChessman(target->getX(), target->getY());
    cout << "[LIST]" ;
    for (auto point: *possibleMoves)
        cout << " [" << point->getX() << "," << point->getY() << " ] "; 
    cout << endl << "[WHILE]" ;
    auto it = possibleMoves->begin();
    while (it != possibleMoves->end())
    {
        int x = (*it)->getX();
        int y = (*it)->getY();

        if (board->isOccupied(x, y))
        {
            IChessman *chessmen = board->getChessman(x, y);
            if (chessmen->getTeam() == targetChessmen->getTeam())
            {
                it = possibleMoves->erase(it);
            }
            else
            {
                it++;
            }
        }
        else{
            it++;
        }
    }
    return *this;
}
