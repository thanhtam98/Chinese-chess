#pragma once

#include "ILabel.h"
#include <string>

union CrossChar {
    struct bits {
        char up:1;
        char down:1;
        char right:1;
        char left:1;
        char asterisk:1;
    } bits;
    int value;
};

enum {
    NON_LEFT = 0b00111,
    NON_RIGHT = 0b01011,
    NON_UP = 0b01110,
    NON_DOWN = 0b01101,
    NON_LEFT_RIGHT = 0b00011,
    NON_RIGHT_DOWN = 0b01001,
    NON_LEFT_DOWN = 0b00101,
    NON_RIGHT_UP = 0b01010,
    NON_LEFT_UP = 0b00110,
    FULL = 0b01111,
    FULL_ASTERISK = 0b11111,
    NON_LEFT_ASTERISK = 0b10111,
    NON_RIGHT_ASTERISK = 0b11011
};

class SpaceLabel : public ILabel {
public:
    SpaceLabel(FWidget* parent, Point* pos): ILabel{parent, pos} {};
    ~SpaceLabel() {};
    void initLayout() override;
    void onMouseDown(FMouseEvent* event) override;
    void setTarget() override;
    void unsetTarget() override;
    void changePosition(Point* to) override;
private:
    std::string getCrossText();
};