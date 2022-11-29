#include "rule/behaviorProvider/defaultBehaviorProvider.h"
#include <vector>
#include "logic/iChessman.h"
#include "logic/iBoard.h"

bool DefaultBehaviorProvider::predicate(Point *point, Rule &rule) {
    return true;
}

void DefaultBehaviorProvider::handleTrue(Point *point, Rule &rule) {
    std::vector<Point*> *possibleMoves = &(rule.possibleMoves);
    possibleMoves->push_back(point);
}

void DefaultBehaviorProvider::handleFalse(Point *point, Rule &rule) {
    std::vector<Point*> *possibleMoves = &(rule.possibleMoves);
    IChessman *chessman;
    IBoard *board = rule.board;
    Point* target = rule.target;
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