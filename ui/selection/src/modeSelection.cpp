#include "modeSelection.h"
#include <memory>
#include "log.h"
#include "ITurn.h"
#include "configDialog.h"

using namespace std;

ModeSelection::ModeSelection(FDialog* parent) {
    _parent = parent;
    buttonGroup = new FButtonGroup(MODE_SELECTION_LABEL, parent);
    buttonGroup->setGeometry (FPoint{2, 15}, FSize{41, 5});

    options.resize(2);
    options[ONLINE_OPTION] = new FRadioButton(ONLINE, buttonGroup);
    options[ONLINE_OPTION]->setGeometry(FPoint{4, 2}, FSize{10, 1});

    options[OFFLINE_OPTION] = new FRadioButton(OFFLINE, buttonGroup);
    options[OFFLINE_OPTION]->setGeometry(FPoint{25, 2}, FSize{10, 1});

    // Temporarily set OFFLINE as default
    options[OFFLINE_OPTION]->setChecked();
    options[OFFLINE_OPTION]->setFocus();

    one = new FTextView(parent);
    one->setText("▐███▌\n▐███▌");
    addHighlight(one, red);
    one->setGeometry(FPoint{2, 3}, FSize{7, 4});

    two = new FTextView{parent};
    two->setText("▐███▌\n▐███▌");
    addHighlight(two, noTeam);
    two->setGeometry(FPoint{12, 3}, FSize{7, 4});

    both = new FTextView{parent};
    both->setText("▐███▌\n▐███▌");
    addHighlight(both, red);
    both->setGeometry(FPoint{30, 3}, FSize{7, 4});

    divider = new FLabel{parent};
    divider->setText("┊\n┊\n┊\n┊\n┊\n┊\n┊\n┊\n┊");
    divider->setGeometry(FPoint{22, 3}, FSize{1, 10});

    connector = new FLabel{parent};
    connector->setText("╌╌╌");
    connector->setGeometry(FPoint{9, 5}, FSize{3, 1});

    online = new FLabel{parent};
    online->setText(ONLINE);
    online->setBackgroundColor(FColor::Green);
    online->setForegroundColor(FColor::White);
    online->setGeometry(FPoint{8, 7}, FSize{6, 1});

    offline = new FLabel{parent};
    offline->setText(OFFLINE);
    offline->setBackgroundColor(FColor::Blue);
    offline->setForegroundColor(FColor::White);
    offline->setGeometry(FPoint{30, 7}, FSize{7, 1});

    FStyle style;
    style.setStyle(Style::Italic + Style::Dim);
    FTextView::FTextHighlight italic{0, 22, style};

    onlineDesc = new FTextView{parent};
    onlineDesc->setText(ONLINE_DESC);
    onlineDesc->setForegroundColor(DESC_COLOR);
    addHighlight(onlineDesc, italic, 3);
    onlineDesc->setGeometry(FPoint{1, 8}, FSize{21, 5});

    offlineDesc = new FTextView{parent};
    offlineDesc->setText(OFFLINE_DESC);
    offlineDesc->setForegroundColor(DESC_COLOR);
    addHighlight(offlineDesc, italic);
    offlineDesc->setGeometry(FPoint{23, 8}, FSize{22, 4});
}

void ModeSelection::addHighlight(FTextView* view, FTextView::FTextHighlight &highlight, int end) {
    for (int i = 0; i < end; i++) {
        view->addHighlight(i, highlight);
    }
}

void ModeSelection::initHook() {
    turnTimerId = _parent->addTimer(INTERVAL);
}

void ModeSelection::addDebugTrick() {
    options.resize(3);
    FRadioButton *debugButton = new FRadioButton(DEBUG, buttonGroup);
    debugButton->setGeometry(FPoint{4, 3}, FSize{10, 1});
    debugButton->back();
    debugButton->setChecked();
    options[DEBUG_OPTION] = debugButton;
}

int ModeSelection::select(){
    for (auto n = 1; n <= int(buttonGroup->getCount()); n++) {
        if (buttonGroup->isChecked(n)) {
            FString mode = buttonGroup->getButton(n)->getText();
            LOG_F("Select: %s", mode.c_str());
            if (mode == DEBUG) {
                ITurn::newDebugTurns();
                return DEBUG_OPTION;
            }
            if (mode == OFFLINE) {
                ITurn::newOfflineTurns();
                return OFFLINE_OPTION;
            }
            if (mode == ONLINE) {
                ITurn::newOnlineTurns();
                return ONLINE_OPTION;
            }
        }
    }
    return ONLINE_OPTION;
}

void ModeSelection::setFocus() {
    options[OFFLINE_OPTION]->setFocus();
    RadioButtonChain::setFocus();
}

void ModeSelection::show() {
    one->show();
    two->show();
    both->show();
    divider->show();
    connector->show();
    online->show();
    offline->show();
    onlineDesc->show();
    offlineDesc->show();
    RadioButtonChain::show();
}

void ModeSelection::hide() {
    one->hide();
    two->hide();
    both->hide();
    divider->hide();
    connector->hide();
    online->hide();
    offline->hide();
    onlineDesc->hide();
    offlineDesc->hide();
    _parent->delTimer(turnTimerId);
    RadioButtonChain::hide();
}

void ModeSelection::onTimer(FTimerEvent* event) {
    static bool toggle = false;
    if (event->getTimerId() == turnTimerId) {
        if (toggle) {
            addHighlight(one, red);
            addHighlight(two, noTeam);
            addHighlight(both, red);
        } else {
            addHighlight(one, noTeam);
            addHighlight(two, black);
            addHighlight(both, black);
        }
        toggle = (toggle == false);
        _parent->redraw();
    }
}