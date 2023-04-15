#pragma once

#include "ui/button/IButton.h"

class PieceButton : public IButton{

public:
    explicit PieceButton(FWidget* = nullptr);
    void initLayout() override;
    Point* getPosition() override;  
};