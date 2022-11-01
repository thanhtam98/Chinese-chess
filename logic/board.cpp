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
IChessman* Board::getChessman(int x, int y){
    return nullptr;
}