#include "logic/board.h"

Board* Board::getInstance() {
    if (instance == nullptr) {
        return instance = new Board();
    }
    return instance;
}
