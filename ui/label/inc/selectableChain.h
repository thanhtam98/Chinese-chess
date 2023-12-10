#pragma once
#include "iChain.h"

class SelectableChain: public IChain {
public:
    virtual void select() = 0;
    virtual void hide() = 0;
    virtual void show() = 0;

    virtual IChain* next(int branch = 0) override;
    virtual IChain* setNext(IChain* next, int branch = 0) override;
    virtual IChain* back() override;
};