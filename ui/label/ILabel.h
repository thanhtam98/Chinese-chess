#pragma once

#include "final/final.h"
#include "utils/point.h"

using namespace finalcut;

class ILabel : public FLabel {
public:
    ILabel(FWidget* parent, Point* pos) : FLabel{parent}, pos{pos} {};
    Point* getPosition();
    bool isTargeted();
    virtual void setTarget() = 0;
    virtual void unsetTarget() = 0;
    virtual void changePosition(Point* to) = 0;
protected:
    Point *pos;
    bool target;
};