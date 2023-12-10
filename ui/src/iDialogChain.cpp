#include "iDialogChain.h"

IChain* IDialogChain::next(int branch) {
    hide();
    if (hasNext(branch)) {
        IDialogChain* next = (IDialogChain*) branches[branch];
        next->show();
    }
    close();
    return IChain::next(branch);
}

IChain* IDialogChain::setNext(IChain* next, int branch) {
    IDialogChain* nextDialog = (IDialogChain*) next;
    nextDialog->hide();
    return IChain::setNext(next, branch);
}