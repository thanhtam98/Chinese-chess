#pragma once
#include "final/final.h"
// #include "iBoard.h"
// #include "utils.h"
// #include "ILabel.h"
// #include "riverBorderLabels.h"
// #include "fortressLabels.h"
// #include "verticalLineLabels.h"
// #include "horizontalLabels.h"
// #include "debugLabel.h"
// #include "utils.h"
// #include "teamSignalLabels.h"
// #include "endGameLabel.h"
// #include "introLabel.h"
// #include <vector>
// #include <string>
#include "introDialog.h"
#include "boardDialog.h"

using namespace finalcut;

// class MoveManager;

#define MAIN_DIALOG_POINT FPoint{1,1}
#define WINDOW_WIDTH 46
#define WINDOW_LENGTH 26
#define WINDOW_SIZE FSize{WINDOW_WIDTH, WINDOW_LENGTH}

class MainDialog : public FDialog {
public:
    explicit MainDialog(FWidget* = nullptr);

    friend class MoveManager;

    // void dispatchChessmanMove(Point* source, Point* destination);
    void initLayout() override;
    // void clickedCallback();
    // void moveCallback();

    // void onTimer(FTimerEvent* event) override;

    // MoveManager* moveManager;

private:
    // void addCallback(ILabel* label, std::string event);

    // IBoard* board;
    // RiverBorderLabels riverBoundaryLabels{this};
    // FortressLabels fortressLabels{this};
    // VerticleLineLabels verticleLineLabels{this};
    // HorizontalLineLabels horizontalLineLabels{this};
    // TeamSignalLabels *teamSignalLabels;
    // DebugLabel debugLabel{this};
    // ILabel* pieces[BOARD_WIDTH][BOARD_LENGTH];
    // EndGameLabel endGameLabel{this};
    IntroDialog *introDialog;
    BoardDialog *boardDialog;
};