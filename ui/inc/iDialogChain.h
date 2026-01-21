#pragma once
#include "final/final.h"
#include "iChain.h"

using namespace finalcut;

class IDialogChain: public FDialog, public IChain {
public:
    explicit IDialogChain(FDialog* parent): FDialog{parent} {};

    virtual IChain* next(int branch = 0) override;
    virtual IChain* setNext(IChain* next, int branch = 0) override;

    virtual inline void initHook() {};
protected:
};