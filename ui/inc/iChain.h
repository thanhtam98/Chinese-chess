#pragma once

class IChain {
public:
    virtual void setNext(IChain* next);
    virtual IChain* next();
    virtual bool hasNext();
protected:
    IChain* nextChain;
};