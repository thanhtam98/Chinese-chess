#include "rule/behaviorProvider/chariotBehaviorProvider.h"

bool ChariotBehaviorProvider::predicate(Point *point, Rule &rule) {
    IBoard *board = rule.getIBoard();
    return !board->isOccupied(point->getX(), point->getY());
}