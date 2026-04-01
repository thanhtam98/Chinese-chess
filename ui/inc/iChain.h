#pragma once
#include <vector>
#include <string>

class IChain {
public:
    static const int ALL_BRANCHES = -1;
    virtual IChain* setNext(IChain* next, int branch = 0);
    virtual IChain* next(int branch = 0);
    virtual bool hasNext(int branch = 0);
    virtual IChain* back();
    virtual bool hasBack();
    std::string name;
protected:
    std::vector<IChain*> branches;
    IChain* prevChain = nullptr;
};