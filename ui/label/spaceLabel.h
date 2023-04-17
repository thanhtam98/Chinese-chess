#pragma once

#include "ui/label/ILabel.h"
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
    NON_LEFT = 0b0111,
    NON_RIGHT = 0b1011,
    NON_UP = 0b1110,
    NON_DOWN = 0b1101,
    NON_LEFT_RIGHT = 0b0011,
    NON_RIGHT_DOWN = 0b1001,
    NON_LEFT_DOWN = 0b0101,
    NON_RIGHT_UP = 0b1010,
    NON_LEFT_UP = 0b0110,
    FULL = 0b1111
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