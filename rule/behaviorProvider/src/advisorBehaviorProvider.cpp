#include "advisorBehaviorProvider.h"
#include <vector>
#include "iChessman.h"
#include "iBoard.h"
#include <iostream>

bool AdvisorBehaviorProvider::predicate(Point *point) { return false;
}

void AdvisorBehaviorProvider::handleTrue(Point *point) {

}

void AdvisorBehaviorProvider::handleFalse(Point *point) {
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
    // std::cout << *point << " in palace" << endl;

    if (!board->isOccupied(point->getX(),point->getY())){
        possibleMoves->push_back(point);
        return;
    }

    IChessman *targetChessman = board->getChessman(x,y);
    chessman = board->getChessman(point->getX(),point->getY());

    if (chessman && chessman->getTeam() != targetChessman->getTeam()){
        possibleMoves->push_back(point);
    }
}

vector<direction_code> AdvisorBehaviorProvider::getListDir(){
    return {NORTH_WEST,
            NORTH_EAST,
            SOUTH_WEST,
            SOUTH_EAST};
}
