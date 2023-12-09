#include "iChain.h"

IChain* IChain::setNext(IChain* next) {
    this->nextChain = next;
    next->prevChain = this;
    return this;
}

IChain* IChain::next() {
    return nextChain;
}

bool IChain::hasNext() {
    return nextChain != nullptr;
}

IChain* IChain::back() {
    return prevChain;
}

bool IChain::hasBack() {
    return prevChain != nullptr;
}
