#pragma once
#include "final/final.h"
#include "selectableChain.h"
#include <string>

using namespace finalcut;

class WaitableChain: public SelectableChain {
public:
    static const int DONE = 0;
    static const int FAILED = 1;
    static const int INTERVAL = 20000;

    explicit WaitableChain(FDialog* _parent, FButton* okButton);

    virtual int select() override;
    virtual void hide() override;
    virtual void show() override;
    virtual void setFocus() override;
    virtual void initHook() override;
    void onTimer(FTimerEvent* event);
    void setDone(bool value);
protected:
    const std::string WAITING_LABEL = "Please wait...";
    const std::string SUCCESS_LABEL = "Successfully connect!";
    const std::string FAIL_LABEL = "Failed! Please try again";

    enum status {
        SUCCESS,
        FAILURE,
        NOT_IDENTIFIED
    };

    FDialog* parent;
    FLabel* waitingLabel;
    FButton* okButton;
    status done = NOT_IDENTIFIED;
    int waitingTimerId;
};