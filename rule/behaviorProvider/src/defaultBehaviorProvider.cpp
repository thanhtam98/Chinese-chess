#include "defaultBehaviorProvider.h"
#include <vector>
#include "iChessman.h"
#include "iBoard.h"

bool DefaultBehaviorProvider::predicate(Point *point) {
    return true;
}

void DefaultBehaviorProvider::handleTrue(Point *point) {
    std::vector<Point*> *possibleMoves = rule.getPossibleMove();
    possibleMoves->push_back(point);
}

void DefaultBehaviorProvider::handleFalse(Point *point) {
    std::vector<Point*> *possibleMoves = rule.getPossibleMove();
    IChessman *chessman;
    IBoard *board = rule.getIBoard();
    Point* target = rule.getTarget();
    int x = target->getX();
    int y = target->getY();

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

void DefaultBehaviorProvider::handleBefore() { }

void DefaultBehaviorProvider::handleAfter() { }

vector<direction_code> DefaultBehaviorProvider::getListDir(){
    return {WEST, EAST, NORTH, SOUTH};
}
