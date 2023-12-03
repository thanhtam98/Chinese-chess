#include "iChain.h"

void IChain::setNext(IChain* next) {
    this->nextChain = next;
}

IChain* IChain::next() {
    return nextChain;
}

bool IChain::hasNext() {
    return nextChain != nullptr;
}
