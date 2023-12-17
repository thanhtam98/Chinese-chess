#include "configDialog.h"
#include "mainDialog.h"
#include "teamSelection.h"
#include "hostSelection.h"
#include "ipSelection.h"
#include "ipListSelection.h"

ConfigDialog::ConfigDialog(FDialog* parent): IDialogChain{parent} {
    setText("Configuration Dialog");
    setGeometry(MAIN_DIALOG_POINT, WINDOW_SIZE);
    modeSelection = new ModeSelection{this};
    TeamSelection* teamSelection = new TeamSelection{this};
    HostSelection* hostSelection = new HostSelection{this};
    IpSelection* ipSelection = new IpSelection{this};
    IpListSelection* ipListSelection = new IpListSelection{this};
    serverWaitableChain = new WaitableChain{this, &ok};
    clientWaitableChain = new WaitableChain{this, &ok};

    modeSelection->setNext(hostSelection, ModeSelection::ONLINE_OPTION);
    modeSelection->setNext(teamSelection, ModeSelection::OFFLINE_OPTION);
    hostSelection->setNext(ipSelection, HostSelection::NO_OPTION);
    hostSelection->setNext(ipListSelection, HostSelection::YES_OPTION);
    ipSelection->setNext(clientWaitableChain);
    ipListSelection->setNext(serverWaitableChain);
    currentSelection = modeSelection;

    ok.front();
    ok.setGeometry(FPoint{34, 20}, FSize{8, 1});
    ok.addCallback(
        "clicked",
        this,
        &ConfigDialog::okCallback
    );

    back.front();
    back.setGeometry(FPoint{24, 20}, FSize{8, 1});
    back.addCallback(
        "clicked",
        this,
        &ConfigDialog::backCallback
    );
    back.hide();
}

void ConfigDialog::okCallback() {
    int branch = currentSelection->select();
    if (currentSelection->hasNext(branch)) {
        currentSelection = (SelectableChain*) currentSelection->next(branch);
        if (currentSelection->hasBack()) {
            back.show();
        }
    } else {
        next();
    }
}

void ConfigDialog::backCallback() {
    currentSelection = (SelectableChain*) currentSelection->back();
    if (!currentSelection->hasBack()) {
        back.hide();
    }
}

void ConfigDialog::onKeyPress(FKeyEvent* event) {
    const auto key_id = event->key();
    auto key_name = finalcut::FVTerm::getFOutput()->getKeyName(key_id);
    LOG_F("Key %s", key_name.c_str());
    if (key_name == "d" || key_name == "D") {
        modeSelection->addDebugTrick();
        // redraw();
    }
}

void ConfigDialog::onTimer(FTimerEvent* event) {
    serverWaitableChain->onTimer(event);
    clientWaitableChain->onTimer(event);
    modeSelection->onTimer(event);
}

void ConfigDialog::initHook() {
    modeSelection->initHook();
}