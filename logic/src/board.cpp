#include "board.h"
#include "chessman.h"
#include <iostream>

IBoard* Board::instance = nullptr;
IBoard* Board::getInstance() {
    if (instance == nullptr) {
        instance = new Board();
        ((Board*) instance)->setup();
    }
    return instance;
}

Board::Board(IBoard *t)
{
    for (int x = 0; x < BOARD_WIDTH; x++){
        for (int y = 0; y < BOARD_LENGTH; y++){
            if (t->getChessman(x, y) != nullptr){
                map[x][y] = Chessman::newInstance(
                    Piece(t->getChessman(x, y)->getCode(),
                          t->getChessman(x, y)->getTeam()),
                    Point::of(x, y));

                if (map[x][y]->getCode() == GENERAL){
                    setGeneralLocation(map[x][y]->getTeam(), Point::of(x, y));
                }
            }
            else{
                map[x][y] = nullptr;
            }
        }
    }
}

bool Board::isOccupied (int x, int y) {
    if (!Point::isWithinBoundary(x, y)) return false;
    return (map[x][y] != nullptr);
}

bool Board::isOccupied (Point *point) {
    return (map[point->getX()][point->getY()] != nullptr);
}

IChessman* Board::getChessman(int x, int y) {
    if (!Point::isWithinBoundary(x, y)) return nullptr;
    return map[x][y];
}

IChessman* Board::getChessman(Point *point) {
    return map[point->getX()][point->getY()];
}

void Board::move(Point* from, Point* to) {
    IChessman* fromChessman = getChessman(from);
    if (isOccupied(to)) {
        IChessman* toChessman = getChessman(to);
        if (toChessman->getCode() == GENERAL) {
            LOG_F("Game ends. Team %s wins.", fromChessman->getTeam() == RED ? "RED" : "BLACK");
            endGame(fromChessman->getTeam());
        }
        delete toChessman;
    } 
    map[to->getX()][to->getY()] = fromChessman;
    map[from->getX()][from->getY()] = nullptr;

    fromChessman->move(to);

    /* Cache General locaion in order to fast checkmate */
    if (fromChessman->getCode() == GENERAL){
        setGeneralLocation(fromChessman->getTeam(), to);
    }
}

std::vector<Point*> Board::getPossibleMoves(Point* target) {
    IChessman* chessman = getChessman(target);
    if (chessman) {
        return chessman->getPossibleMoves();
    } else {
        return {};
    }
}

Point* Board::getGeneralLocation(team_code team){
    return generalLocation[team];
}
void Board::setGeneralLocation(team_code team, Point* location){
    generalLocation[team] = location;
}
void Board::setup() {
    Piece pieces[BOARD_LENGTH][BOARD_WIDTH] = 
    { {{CHARIOT, RED}, {HORSE, RED}, {ELEPHANT, RED}, {ADVISOR, RED}, {GENERAL, RED}, {ADVISOR, RED}, {ELEPHANT, RED}, {HORSE, RED}, {CHARIOT, RED} },
      {{C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}},
      {{C_NONE, T_NONE}, {CANNON, RED}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {CANNON, RED}, {C_NONE, T_NONE}},
      {{SOLDIER, RED}, {C_NONE, T_NONE}, {SOLDIER, RED}, {C_NONE, T_NONE}, {SOLDIER, RED}, {C_NONE, T_NONE}, {SOLDIER, RED}, {C_NONE, T_NONE}, {SOLDIER, RED}},
      {{C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}},
      {{C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}},
      {{SOLDIER, BLACK}, {C_NONE, T_NONE}, {SOLDIER, BLACK}, {C_NONE, T_NONE}, {SOLDIER, BLACK}, {C_NONE, T_NONE}, {SOLDIER, BLACK}, {C_NONE, T_NONE}, {SOLDIER, BLACK}},
      {{C_NONE, T_NONE}, {CANNON, BLACK}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {CANNON, BLACK}, {C_NONE, T_NONE}},
      {{C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}, {C_NONE, T_NONE}},
      {{CHARIOT, BLACK}, {HORSE, BLACK}, {ELEPHANT, BLACK}, {ADVISOR, BLACK}, {GENERAL, BLACK}, {ADVISOR, BLACK}, {ELEPHANT, BLACK}, {HORSE, BLACK}, {CHARIOT, BLACK} }
    };

    Piece blank = {C_NONE, T_NONE};
    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_LENGTH; y++) {
            if (pieces[y][x] != blank) {
                // becarefull: 
                // x is the line number
                // y is the column number
                map[x][y] = Chessman::newInstance(pieces[y][x], Point::of(x,y));
                if (map[x][y]->getCode() == GENERAL){
                    setGeneralLocation(map[x][y]->getTeam(), Point::of(x,y));
                }
            } else {
                map[x][y] = nullptr;
            }
        }
    }
}

void Board::endGame(team_code _winningTeam) {
    isGameOver = true;
    winningTeam = _winningTeam;
}