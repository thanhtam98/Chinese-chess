#include "logic/board.h"

Board* Board::instance = nullptr;
Board* Board::getInstance() {
    if (instance == nullptr) {
        return instance = new Board();
    }
    return instance;
}

bool Board::isOccupied (Point *point) {
    return true;
}
IChessman* Board::getChessman(Point *point){
    return nullptr;
}