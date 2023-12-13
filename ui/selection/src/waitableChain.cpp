#include "waitableChain.h"

WaitableChain::WaitableChain(FDialog* _parent, FButton* _okButton) {
    parent = _parent;
    waitingLabel = new FLabel{_parent};
    waitingLabel->setText(WAITING_LABEL);
    waitingLabel->setGeometry(FPoint{1, 1}, FSize{40, 1});

    okButton = _okButton;
}

void WaitableChain::initHook() {
    waitingTimerId = parent->addTimer(INTERVAL);
    okButton->setDisable();
    parent->redraw();
}

int WaitableChain::select() {
    if (done == SUCCESS) {
        return DONE;
    } else if (done == FAILURE) {
        // return to the previous confiuration step
        if (branches.size() <= FAILED) {
            branches.resize(FAILED);
        }
        branches[FAILED] = prevChain;
        done = NOT_IDENTIFIED;
        waitingLabel->setText(WAITING_LABEL);
        return FAILED;
    }
    return FAILED;
}

void WaitableChain::setDone(bool value) {
    if (value) {
        done = SUCCESS;
        waitingLabel->setText(SUCCESS_LABEL);
    } else {
        done = FAILURE;
        waitingLabel->setText(FAIL_LABEL);
    }
    okButton->setEnable();
    parent->redraw();
}

void WaitableChain::onTimer(FTimerEvent* event) {
    if (event->getTimerId() == waitingTimerId) {
        waitingLabel->setText(FAIL_LABEL);
        okButton->setEnable();
        parent->redraw();
        parent->delTimer(waitingTimerId);
        done = FAILURE;
    }
}

void WaitableChain::hide() {
    waitingLabel->hide();
}

void WaitableChain::show() {
    waitingLabel->show();
}

void WaitableChain::setFocus() {
    waitingLabel->setFocus();
}