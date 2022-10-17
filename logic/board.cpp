#include "logic/board.h"

Board* Board::instance = nullptr;
Board* Board::getInstance() {
    if (instance == nullptr) {
        return instance = new Board();
    }
    return instance;
}
