#include "generalBehaviorProvider.h"
#include "iBoard.h"
#include "iChessman.h"
#include "point.h"
#include <iostream>

bool GeneralBehaviorProvider::predicate(Point *point, Rule &rule) {
    return false;
}


void GeneralBehaviorProvider::handleFalse(Point *point, Rule &rule) {
    std::vector<Point*> *possibleMoves = rule.getPossibleMove();
    IChessman *chessman;
    IBoard *board = rule.getIBoard();
    Point* target = rule.getTarget();
    int x = target->getX();
    int y = target->getY();

    if (!point->isWithinPalace()) {
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