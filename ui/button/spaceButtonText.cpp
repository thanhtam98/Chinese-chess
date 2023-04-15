#include "ui/button/spaceButtonText.h"
#include "utils/constant.h"

std::string SpaceButtonText::getText(int x, int y) {
    char up = 1, down = 1, left = 1, right = 1;

    if (x == 0) left = 0;
    if (x == BOARD_WIDTH-1) right = 0;
    if (y == 0 || (y == BOARD_LENGTH/2 && x != 0 && x != BOARD_WIDTH-1)) 
        up = 0;
    if (y == BOARD_LENGTH-1 || (y == BOARD_LENGTH/2-1 &&
        x != 0 && x != BOARD_WIDTH-1)) 
        down = 0;

    CrossChar crossChar = { .bits{up, down, right, left} };
    std::string text;
    switch (crossChar.value)
    {
    case NON_LEFT:
        text = "├─";
        break;
    
    case NON_RIGHT:
        text = "┤ ";
        break;

    case NON_UP:
        text = "┬─";
        break;

    case NON_DOWN:
        text = "┴─";
        break;

    case NON_LEFT_RIGHT:
        text = "──";
        break;

    case FULL:
        text = "┼─";
        break;

    default:
        text = "  ";
        break;
    }
    return text;
}