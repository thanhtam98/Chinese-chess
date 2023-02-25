#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector>
#include "logic/iChessman.h"
#include "utils/constant.h"
#include "logic/iBoard.h"
#include "utils/point.h"
/**
 * @brief This is the implementation of the IBoard interface
 * It creates and manages all chessmen infomation
 * It also provides some relative functions.
 * @param
 * 
*/
class Board : public IBoard{
public:
    /* Singleton */
    static IBoard* getInstance();
    bool isOccupied (int x, int y);
    bool isOccupied (Point *point);
    IChessman* getChessman(int x, int y);
    IChessman* getChessman(Point *point);
    bool move(Point* from, Point* to);
private:
    Board() {};
    /* The single instance for Singleton */
    static IBoard* instance;
    /* Intantiate chessmen and put them into the map */
    void setup();
};

#endif