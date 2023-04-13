#pragma once

#include "ui/IButton.h"

class PieceButton : public IButton{

public:
    explicit PieceButton(FWidget* = nullptr);
    void initLayout() override;
    Point* getPosition() override;  
};