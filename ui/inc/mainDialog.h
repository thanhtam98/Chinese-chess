#pragma once
#include "final/final.h"
#include "iBoard.h"
#include "utils.h"
#include "ILabel.h"
#include "riverBorderLabels.h"
#include "fortressLabels.h"
#include "verticalLineLabels.h"
#include "horizontalLabels.h"
#include "debugLabel.h"
#include "utils.h"
#include "teamSignalLabels.h"
// #include "moveManager.h"
#include <vector>
#include <string>

using namespace finalcut;

class MoveManager;

const int PIECE_SIZE_X = 2;
const int PIECE_SIZE_Y = 1;
const int SPACE_SIZE_X = 3;
const int SPACE_SIZE_Y = 1;
const int SPACE_BW_PIECE_X = PIECE_SIZE_X + SPACE_SIZE_X;
const int SPACE_BW_PIECE_Y = PIECE_SIZE_Y + SPACE_SIZE_Y;
const int OFFSET_X = 2;
const int OFFSET_Y = 2;
const int SPACE_LABEL_SIZE_X = 3;
const int SPACE_LABEL_SIZE_Y = 1;
const FColor BLACK_BG = FColor::Black;
const FColor FOCUS_BLACK_BG = FColor::Grey50;
const FColor RED_BG = FColor::Red;
const FColor FOCUS_RED_BG = FColor::Red1;
const FColor POTENTIAL_BLACK_BG = FColor::DarkRed;
const FColor POTENTIAL_RED_BG = FColor::LightRed;

class MainDialog : public FDialog {
public:
    explicit MainDialog(FWidget* = nullptr);

    friend class MoveManager;

    void dispatchChessmanMove(Point* source, Point* destination);
    void initLayout() override;
    void clickedCallback();
    void moveCallback();

    MoveManager* moveManager;

private:
    void addCallback(ILabel* label, std::string event);

    IBoard* board;
    RiverBorderLabels riverBoundaryLabels{this};
    FortressLabels fortressLabels{this};
    VerticleLineLabels verticleLineLabels{this};
    HorizontalLineLabels horizontalLineLabels{this};
    TeamSignalLabels *teamSignalLabels;
    DebugLabel debugLabel{this};
    ILabel* pieces[BOARD_WIDTH][BOARD_LENGTH];
};