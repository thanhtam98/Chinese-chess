#include "chariotBehaviorProvider.h"

bool ChariotBehaviorProvider::predicate(Point *point) {
    IBoard *board = rule.getIBoard();
    return !board->isOccupied(point->getX(), point->getY());
}