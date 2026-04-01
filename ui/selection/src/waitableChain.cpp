#include "waitableChain.h"
#include "log.h"
#include <codecvt>

const std::string WaitableChain::WAITING_LABEL = "Please wait...";
const std::string WaitableChain::SUCCESS_LABEL = "Successfully connect!";
const std::string WaitableChain::FAIL_LABEL = "Failed! Please try again";

WaitableChain::WaitableChain(FDialog* _parent, FButton* _okButton, FButton* _backButton, 
    Message _waitingText, Message _successMess, std::string _failedText) {
    name = "waitable";
    parent = _parent;
    waitingText = _waitingText;
    successText = _successMess;
    failedText = _failedText;
    waitingLabel = new FLabel{_parent};
    // waitingLabel->setText(_waitingText);
    waitingLabel->setGeometry(FPoint{2, 16}, FSize{40, 3});
    errorLabel = new FLabel{parent};
    std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> converter;
    std::u16string errorDeco = \                           
u"  ░░░░░░░░░░░░  ░░░░░    ░░  ░░░░░ \n\
  ░█████░█████░░█████░░████▓░█████▓░\n\
 ░██▓▓▓░░█▓░██░▒█░░██░██░░██░██░▒█▓░\n\
░░██░░ ░████▓ ░████░░▒█▓░░██▒████   \n\
░▒█████░██░██▒░█▓░██ ░████▓░██░▒█▓░ \n\
  ░░░░░░░░░░░░░░░░░░ ░░░░░░░░░░░░  ";
    errorLabel->setText(converter.to_bytes(errorDeco));
    errorLabel->setGeometry(FPoint{7, 6}, FSize{41, 6});
    errorLabel->setForegroundColor(FColor::Red2);

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
        waitingLabel->setText(waitingText());
        return FAILED;
    }
    return FAILED;
}

void WaitableChain::setDone(bool value) {
    LOG_F("Done the action and go on with the returned results");
    if (value) {
        done = SUCCESS;
        waitingLabel->setText(successText());
    } else {
        done = FAILURE;
        waitingLabel->setText(failedText + ": \n" + errorMessage);
    }
    // Delete Timer when the waitable action is done
    // parent->delTimer(waitingTimerId);
    errorLabel->show();
    okButton->setEnable();
    backButton->setEnable();
    parent->redraw();
    if (value) {
        okButton->emitCallback("clicked");
    }
}

void WaitableChain::hide() {
    waitingLabel->hide();
    errorLabel->hide();
}

void WaitableChain::runAction() {
    LOG_F("Run the action of the chain");
    if (_predicate != nullptr) {
        try {
            LOG_F("Before the action");
            _predicate().get();
            LOG_F("Complete the action");
            setDone(SUCCESS);
        } catch (const std::exception &e) {
            LOG_F("Error : %s", e.what());
            errorMessage = e.what();
            setDone(FAILURE);
        }
    } else {
        LOG_F("No action is set for WaitableChain");
    }
}

void WaitableChain::show() {
    waitingLabel->setText(waitingText());
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