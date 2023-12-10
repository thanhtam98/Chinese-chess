#include "iChain.h"

IChain* IChain::setNext(IChain* next, int branch) {
    if (branch >= branches.size()) {
        branches.resize(branch + 1);
    }
    branches[branch] = next;
    next->prevChain = this;
    return this;
}

IChain* IChain::next(int branch) {
    return branches[branch];
}

bool IChain::hasNext(int branch) {
    return branches[branch] != nullptr;
}

IChain* IChain::back() {
    return prevChain;
}

bool IChain::hasBack() {
    return prevChain != nullptr;
}
