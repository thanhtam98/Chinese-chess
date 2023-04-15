#pragma once

#include "final/final.h"
#include "utils/point.h"

using namespace finalcut;

class IButton : public FButton {

public:
    virtual Point* getPosition() = 0;
    
private:
    Point *pos;
};