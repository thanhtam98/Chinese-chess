#include "rule/behaviorProvider/generalBehaviorProvider.h"
#include "logic/iBoard.h"
#include "logic/iChessman.h"
#include "utils/point.h"
#include <iostream>

bool GeneralBehaviorProvider::predicate(Point *point, Rule &rule) {
    return false;
}


void GeneralBehaviorProvider::handleFalse(Point *point, Rule &rule) {
    std::vector<Point*> *possibleMoves = &(rule.possibleMoves);
    IChessman *chessman;
    IBoard *board = rule.board;
    Point* target = rule.target;
    int x = target->getX();
    int y = target->getY();

    if (!Point::isWithinPalace(point->getX(), point->getY())) {
        // std::cout << *point << "not in palace" << endl;
        return;
    }
    if (!board->isOccupied(point)){
        possibleMoves->push_back(point);
        return;
    }
    IChessman *targetChessman = board->getChessman(x,y);
    chessman = board->getChessman(point);

    if (chessman && chessman->getTeam() != targetChessman->getTeam()){
        possibleMoves->push_back(point);
    }

}