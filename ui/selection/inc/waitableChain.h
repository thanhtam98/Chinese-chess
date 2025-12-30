#pragma once
#include "final/final.h"
#include "selectableChain.h"
#include <string>

using namespace finalcut;

typedef std::function<bool()> Predicate;

class WaitableChain: public SelectableChain {
public:
    static const int DONE = 0;
    static const int FAILED = 1;
    static const int INTERVAL = 20000;
    static const std::string WAITING_LABEL;
    static const std::string SUCCESS_LABEL;
    static const std::string FAIL_LABEL;

    explicit WaitableChain(FDialog* _parent, FButton* okButton, FButton* backButton, 
        std::string waitingText = WAITING_LABEL,
        std::string sucessText = SUCCESS_LABEL,
        std::string failedText = FAIL_LABEL
    );

    virtual int select() override;
    virtual void hide() override;
    virtual void show() override;
    virtual void setFocus() override;
    virtual void initHook() override;
    void onTimer(FTimerEvent* event);
    void setDone(bool value);
    void setAction(Predicate predicate);
protected:
    enum status {
        SUCCESS = true,
        FAILURE = false
    };

    FDialog* parent;
    FLabel* waitingLabel;
    FButton* okButton;
    FButton* backButton;
    status done = FAILURE;
    Predicate _predicate;
    int waitingTimerId;
    std::string waitingText;
    std::string successText;
    std::string failedText;

    void runAction();
};