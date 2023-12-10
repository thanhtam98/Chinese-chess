#ifndef __CONSTANT_H__
#define __CONSTANT_H__
#include <string>

using namespace std;

enum team_code {
    RED,
    BLACK,
    TEAM_SIZE,
    T_NONE
};

enum chessman_code {
    GENERAL,
    ADVISOR,
    ELEPHANT,
    HORSE,
    CHARIOT,
    CANNON,
    SOLDIER,
    CHESSMAN_SIZE,
    C_NONE
};

enum direction_code {
    WEST,
    EAST,
    NORTH,
    SOUTH,
    NORTH_WEST,
    NORTH_EAST,
    SOUTH_WEST,
    SOUTH_EAST,
    DIR_SIZE    
};

struct Piece {
    chessman_code c;
    team_code t;
    static string names[CHESSMAN_SIZE];

    Piece() {};
    Piece(chessman_code code, team_code team): c{code}, t{team} {};

    bool operator!=(const Piece& other);

    string getChessmanName();
    string getTeamName();
    string getName();
};

enum turn_mode {
    ONLINE,
    OFFLINE,
    DEBUG,
    M_NONE
};

extern string chessman_name[TEAM_SIZE][CHESSMAN_SIZE];

const std::string RED_TEAM = "Red";
const std::string BLACK_TEAM = "Black";

#define BOARD_WIDTH      9   // x-axis
#define BOARD_LENGTH     10  // y-axis
#define FRONTIER         4

#endif