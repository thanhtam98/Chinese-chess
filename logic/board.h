#ifndef __BOARD_H__
#define __BOARD_H__
#include "logic/chessman.h"
#include "utils/constant.h"
#include <vector>

class Board {
public:
    Board* getInstance();
    std::vector<Point*> get();
private:
    Board() {};
    Board* instance;
    IChessman* chessmen[BOARD_WIDTH][BOARD_LENGTH];
};

#endif