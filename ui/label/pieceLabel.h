#pragma once

#include "ui/label/ILabel.h"

class PieceLabel : public ILabel {

public:
    PieceLabel(FWidget* parent, Point* pos): ILabel{parent, pos} {};
    void initLayout() override;
    void onMouseDown(FMouseEvent* event) override;
    void setTarget() override;
    void unsetTarget() override;
};