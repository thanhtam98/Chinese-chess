#include "advisorBehaviorProvider.h"
#include <vector>
#include "iChessman.h"
#include "iBoard.h"
#include <iostream>

bool AdvisorBehaviorProvider::predicate(Point *point, Rule &rule) { return false;
}

void AdvisorBehaviorProvider::handleTrue(Point *point, Rule &rule) {

}

void AdvisorBehaviorProvider::handleFalse(Point *point, Rule &rule) {
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

vector<direction_code> AdvisorBehaviorProvider::getListDir(Rule &rule){
    return {NORTH_WEST,
            NORTH_EAST,
            SOUTH_WEST,
            SOUTH_EAST};
}
