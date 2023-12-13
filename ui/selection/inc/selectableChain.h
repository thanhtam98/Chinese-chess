#pragma once
#include "iChain.h"

class SelectableChain: public IChain {
public:
    virtual int select() = 0;
    virtual void hide() = 0;
    virtual void show() = 0;
    virtual void setFocus() = 0;
    virtual inline void initHook();

    virtual IChain* next(int branch = 0) override;
    virtual IChain* setNext(IChain* next, int branch = 0) override;
    virtual IChain* back() override;
};