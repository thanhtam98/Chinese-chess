#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector>
#include "iChessman.h"
#include "constant.h"
#include "iBoard.h"
#include "point.h"
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
    void move(Point* from, Point* to) override;
    std::vector<Point*> getPossibleMoves(Point* target) override;
private:
    Board() {};
    /* The single instance for Singleton */
    static IBoard* instance;
    /* Intantiate chessmen and put them into the map */
    void setup();
};

#endif