#ifndef __CONSTANT_H__
#define __CONSTANT_H__
#include <string>

using namespace std;

enum team_code {
    RED,
    BLACK,
    TEAM_SIZE
};

enum chessman_code {
    GENERAL,
    ADVISOR,
    ELEPHANT,
    HORSE,
    CHARIOT,
    CANNON,
    SOLDIER,
    CHESSMAN_SIZE
};

extern string chessman_name[TEAM_SIZE][CHESSMAN_SIZE];

#define BOARD_WIDTH      9
#define BOARD_LENGTH     10
#define FRONTIER         4

#endif