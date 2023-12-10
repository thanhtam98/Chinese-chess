#pragma once
#include <vector>

class IChain {
public:
    virtual IChain* setNext(IChain* next, int branch = 0);
    virtual IChain* next(int branch = 0);
    virtual bool hasNext(int branch = 0);
    virtual IChain* back();
    virtual bool hasBack();
protected:
    std::vector<IChain*> branches;
    IChain* prevChain;
};