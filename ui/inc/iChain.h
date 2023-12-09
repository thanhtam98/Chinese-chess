#pragma once

class IChain {
public:
    virtual IChain* setNext(IChain* next);
    virtual IChain* next();
    virtual bool hasNext();
    virtual IChain* back();
    virtual bool hasBack();
protected:
    IChain* nextChain;
    IChain* prevChain;
};