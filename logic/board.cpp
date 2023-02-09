#include "logic/board.h"

Board* Board::instance = nullptr;
Board* Board::getInstance() {
    if (instance == nullptr) {
        return instance = new Board();
    }
    return instance;
}

bool Board::isOccupied (int x, int y) {
    return true;
}
bool Board::isOccupied (Point *point) {
    return true;
}
IChessman* Board::getChessman(int x, int y){
    return nullptr;
}
IChessman* Board::getChessman(Point *point){
    return nullptr;
}