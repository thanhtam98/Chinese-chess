#include "configDialog.h"
#include "mainDialog.h"
#include "teamSelection.h"
#include "hostSelection.h"
#include "ipSelection.h"
#include "ipListSelection.h"
#include "wConfig.h"
#include "server.h"
#include "configurator.h"
#include "log.h"

ConfigDialog::ConfigDialog(FDialog* parent): IDialogChain{parent} {
    setText("Configuration");
    setGeometry(MAIN_DIALOG_POINT, WINDOW_SIZE);
    modeSelection = new ModeSelection{this};
    TeamSelection* teamSelectionForModeBranch = new TeamSelection{this};
    TeamSelection* teamSelectionForHostBranch = new TeamSelection{this};
    HostSelection* hostSelection = new HostSelection{this};
    IpSelection* ipSelection = new IpSelection{this};
    IpListSelection* ipListSelection = new IpListSelection{this, &ok};

    auto successMessage0 = []() -> std::string {
        std::string port = Configurator::get(PORT);
        std::string ip = Configurator::get(IP);
        return "The server is now available \non " + ip + ":" + port;
    };
    auto successMessage1 = []() -> std::string {
        return "The client is now ready. Start the game!";
    };
    auto waitingMessage0 = []() -> std::string {
        return "Please wait for the host to be set up...";
    };
    auto waitingMessage1 = []() -> std::string {
        std::string port = Configurator::get(PORT);
        std::string ip = Configurator::get(IP);
        return "The server is now listening on\n" + ip + ":" + port + "\nPlease wait for your opponent!";
    };

    serverWaitableChain = new WaitableChain{this, &ok, &back, 
        waitingMessage0,
        successMessage0
    };
    acceptClientWaitableChain = new WaitableChain{this, &ok, &back,
        waitingMessage1,
        successMessage1
    };
    auto startConnection = []() -> std::future<void> {
        return ConnectionBase::getInstance()->run();
    };
    serverWaitableChain->setAction(startConnection);

    auto scanConnection = []() -> std::future<void> {
        return ConnectionBase::getEnoughConnection();
    };
    acceptClientWaitableChain->setAction(scanConnection);
    
    modeSelection->setNext(hostSelection, ModeSelection::ONLINE_OPTION);
    modeSelection->setNext(teamSelectionForModeBranch, ModeSelection::OFFLINE_OPTION);
    hostSelection->setNext(ipListSelection, HostSelection::SERVER);
    teamSelectionForHostBranch->setNext(serverWaitableChain, IChain::ALL_BRANCHES);
    ipListSelection->setNext(serverWaitableChain, SelectableChain::DONE);
    serverWaitableChain->setNext(hostSelection, WaitableChain::FAILED);
    serverWaitableChain->setNext(acceptClientWaitableChain, WaitableChain::DONE);
    acceptClientWaitableChain->setNext(hostSelection, WaitableChain::FAILED);
    
    clientWaitableChain = new WaitableChain{this, &ok, &back, waitingMessage0, successMessage1};
    hostSelection->setNext(ipSelection, HostSelection::CLIENT);
    ipSelection->setNext(clientWaitableChain, SelectableChain::DONE);
    clientWaitableChain->setAction(startConnection);
    clientWaitableChain->setNext(hostSelection, WaitableChain::FAILED);
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
        LOG_F("Go next to %s", currentSelection->name.c_str());
    } else {
        next();
    }
}

void ConfigDialog::backCallback() {
    currentSelection = (SelectableChain*) currentSelection->back();
    if (!currentSelection->hasBack()) {
        back.hide();
    }
    LOG_F("Go back to %s", currentSelection->name.c_str());
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
    // serverWaitableChain->onTimer(event);
    // clientWaitableChain->onTimer(event);
    modeSelection->onTimer(event);
}

void ConfigDialog::initHook() {
    modeSelection->initHook();
}