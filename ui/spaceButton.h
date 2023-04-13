#pragma once

#include "ui/IButton.h"

class SpaceButton : public IButton{

public:
    explicit SpaceButton(FWidget* = nullptr);
    void initLayout() override;
    Point* getPosition() override;  
};