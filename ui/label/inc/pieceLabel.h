#pragma once

#include "ILabel.h"

class PieceLabel : public ILabel {

public:
    PieceLabel(FWidget* parent, Point* pos): ILabel{parent, pos} {};
    ~PieceLabel();
    void initLayout() override;
    void onMouseDown(FMouseEvent* event) override;
    void setTarget() override;
    void unsetTarget() override;
    void changePosition(Point* to) override;
};