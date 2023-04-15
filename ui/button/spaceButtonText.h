#pragma once

#include <string>

union CrossChar {
    struct bits {
        char up:1;
        char down:1;
        char right:1;
        char left:1;
    } bits;
    int value;
};

enum {
    NON_LEFT = 7,
    NON_RIGHT = 11,
    NON_UP = 14,
    NON_DOWN = 13,
    NON_LEFT_RIGHT = 3,
    FULL = 15
};

class SpaceButtonText {
public:
    // explicit SpaceButtonText(int x, int y);
    static std::string getText(int x, int y);
};