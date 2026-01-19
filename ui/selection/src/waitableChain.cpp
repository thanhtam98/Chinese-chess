#include "waitableChain.h"
#include "log.h"

const std::string WaitableChain::WAITING_LABEL = "Please wait...";
const std::string WaitableChain::SUCCESS_LABEL = "Successfully connect!";
const std::string WaitableChain::FAIL_LABEL = "Failed! Please try again";

WaitableChain::WaitableChain(FDialog* _parent, FButton* _okButton, FButton* _backButton, 
    std::string _waitingText, std::string _sucessText, std::string _failedText) {
    parent = _parent;
    waitingText = _waitingText;
    successText = _sucessText;
    failedText = _failedText;
    waitingLabel = new FLabel{_parent};
    waitingLabel->setText(_waitingText);
    waitingLabel->setGeometry(FPoint{1, 1}, FSize{40, 2});

    okButton = _okButton;
    backButton = _backButton;
    // hide all elements as default
    hide();
}

void WaitableChain::initHook() {
    waitingTimerId = parent->addTimer(INTERVAL);
    // We will hide the the back button, because we don't allow users to go back until 
    // the action of the waiting window successes or fails.
    okButton->setDisable();
    backButton->setDisable();
    parent->redraw();
}

int WaitableChain::select() {
    if (done == SUCCESS) {
        return DONE;
    } else if (done == FAILURE) {
        // // return to the previous confiuration step
        // if (branches.size() <= FAILED) {
        //     branches.resize(FAILED);
        // }
        // branches[FAILED] = prevChain;
        // // done = NOT_IDENTIFIED;
        waitingLabel->setText(waitingText);
        return FAILED;
    }
    return FAILED;
}

void WaitableChain::setDone(bool value) {
    if (value) {
        done = SUCCESS;
        waitingLabel->setText(successText);
        // Delete Timer when success
        parent->delTimer(waitingTimerId);
    } else {
        done = FAILURE;
        waitingLabel->setText(failedText);
    }
    okButton->setEnable();
    parent->redraw();
}

void WaitableChain::onTimer(FTimerEvent* event) {
    if (event && event->getTimerId() == waitingTimerId) {
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

void WaitableChain::runAction() {
    if (_predicate != nullptr){
        _predicate();
        setDone(SUCCESS);
    }
    else {
        LOG_F("No action is set for WaitableChain");
        // setDone(FAILURE);
    }
}

void WaitableChain::show() {
    waitingLabel->show();
    // start the action in a thread
    LOG_F("WaitableChain Show is called");
    std::thread(std::bind(&WaitableChain::runAction, this)).detach();
}

void WaitableChain::setFocus() {
    waitingLabel->setFocus();
}

void WaitableChain::setAction(Predicate predicate) {
    _predicate = predicate;
}