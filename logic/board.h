#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector>
#include "logic/iChessman.h"
#include "utils/constant.h"
#include "logic/iBoard.h"

class Board : public IBoard{
public:
    static Board* getInstance();
    std::vector<Point*> get();
    bool isOccupied (int x, int y);
    IChessman* getChessman(int x, int y);;
private:
    Board() {};
    static Board* instance;
    IChessman* map[BOARD_WIDTH][BOARD_LENGTH];
    
};

#endif