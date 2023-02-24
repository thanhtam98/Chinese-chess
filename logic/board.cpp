#include "logic/board.h"

Board* Board::instance = nullptr;
Board* Board::getInstance() {
    if (instance == nullptr) {
        instance = new Board();
    }
    instance->setup();
    return instance;
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

void Board::setup() {
    Piece pieces[BOARD_LENGTH][BOARD_WIDTH] = 
    { {{.c = CHARIOT, .t = BLACK}, {.c = HORSE, .t = BLACK}, {.c = ELEPHANT, .t = BLACK}, {.c = ADVISOR, .t = BLACK}, {.c = GENERAL, .t = BLACK}, {.c = ADVISOR, .t = BLACK}, {.c = ELEPHANT, .t = BLACK}, {.c = HORSE, .t = BLACK}, {.c = CHARIOT, .t = BLACK} },
      {{.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}},
      {{.c = C_NONE, .t = T_NONE}, {.c = CANNON, .t = BLACK}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = CANNON, .t = BLACK}, {.c = C_NONE, .t = T_NONE}},
      {{.c = SOLDIER, .t = BLACK}, {.c = C_NONE, .t = T_NONE}, {.c = SOLDIER, .t = BLACK}, {.c = C_NONE, .t = T_NONE}, {.c = SOLDIER, .t = BLACK}, {.c = C_NONE, .t = T_NONE}, {.c = SOLDIER, .t = BLACK}, {.c = C_NONE, .t = T_NONE}, {.c = SOLDIER, .t = BLACK}},
      {{.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}},
      {{.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}},
      {{.c = SOLDIER, .t = RED}, {.c = C_NONE, .t = T_NONE}, {.c = SOLDIER, .t = RED}, {.c = C_NONE, .t = T_NONE}, {.c = SOLDIER, .t = RED}, {.c = C_NONE, .t = T_NONE}, {.c = SOLDIER, .t = RED}, {.c = C_NONE, .t = T_NONE}, {.c = SOLDIER, .t = RED}},
      {{.c = C_NONE, .t = T_NONE}, {.c = CANNON, .t = RED}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = CANNON, .t = RED}, {.c = C_NONE, .t = T_NONE}},
      {{.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}, {.c = C_NONE, .t = T_NONE}},
      {{.c = CHARIOT, .t = RED}, {.c = HORSE, .t = RED}, {.c = ELEPHANT, .t = RED}, {.c = ADVISOR, .t = RED}, {.c = GENERAL, .t = RED}, {.c = ADVISOR, .t = RED}, {.c = ELEPHANT, .t = RED}, {.c = HORSE, .t = RED}, {.c = CHARIOT, .t = RED} }
    };

    Piece blank = {.c = C_NONE, .t = T_NONE};
    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_LENGTH; y++) {
            if (pieces[y][x] != blank) {
                map[y][x] = IChessman::newInstance(&pieces[y][x]);
            } else {
                map[y][x] = nullptr;
            }
        }
    }
}