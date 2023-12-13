#pragma once
#include "final/final.h"
#include "selectableChain.h"
#include <vector>

using namespace finalcut;

class RadioButtonChain: public SelectableChain {
public:
    virtual int select() = 0;
    virtual void hide() override;
    virtual void show() override;
    virtual void setFocus() override;
protected:
    FButtonGroup* buttonGroup;
    std::vector<FRadioButton *> options;
};