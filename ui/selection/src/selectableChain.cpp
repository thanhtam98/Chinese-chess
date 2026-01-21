#include "selectableChain.h"

IChain* SelectableChain::next(int branch) {
    hide();
    if (hasNext(branch)) {
        SelectableChain* next = (SelectableChain*) branches[branch];
        next->show();
        next->initHook();
        next->setFocus();
    }
    return IChain::next(branch);
}

IChain* SelectableChain::setNext(IChain* next, int branch) {
    SelectableChain* nextSelection = (SelectableChain*) next;
    nextSelection->hide();
    return IChain::setNext(next, branch);
}

IChain* SelectableChain::back() {
    hide();
    if (hasBack()) {
        SelectableChain* back = (SelectableChain*) prevChain;
        back->show();
        back->initHook();
        back->setFocus();
    }
    return IChain::back();
}