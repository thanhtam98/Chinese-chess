#include "generalBehaviorProvider.h"
#include "iBoard.h"
#include "iChessman.h"
#include "point.h"
#include "log.h"
#include <iostream>

bool GeneralBehaviorProvider::predicate(Point *point) {
    return false;
}


void GeneralBehaviorProvider::handleFalse(Point *point) {
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

void GeneralBehaviorProvider::handleAfter() {
    std::vector<Point*> *possibleMoves = rule.getPossibleMove();
    IBoard *board = rule.getIBoard();
    Point* target = rule.getTarget();
    int x = target->getX();
    int y = target->getY();
    IChessman *targetChessman = board->getChessman(x, y);
    // Check flying general move
    // If the target chessman is Black General, we move up until meeting an
    // occupied chessman
    if (targetChessman->getTeam() == RED) {
        y++;
        while (++y <= BOARD_LENGTH) {
            if (board->isOccupied(x, y)) {
                IChessman* chessman = board->getChessman(x, y);
                if (chessman && chessman->getCode() == GENERAL && chessman->getTeam() == BLACK) {
                    possibleMoves->push_back(Point::of(x, y));
                }
                break;
            }
            y++;
        }
    } else {
        // Otherwise, move down
        y--;
        while (y >= 0) {
            if (board->isOccupied(x, y)) {
                IChessman* chessman = board->getChessman(x, y);
                if (chessman && chessman->getCode() == GENERAL && chessman->getTeam() == RED) {
                    possibleMoves->push_back(Point::of(x, y));
                }
                break;
            }
            y--;
        }
    }
}