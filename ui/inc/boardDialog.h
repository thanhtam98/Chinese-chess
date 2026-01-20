#pragma once
#include "final/final.h"
#include "iBoard.h"
#include "ILabel.h"
#include "riverBorderLabels.h"
#include "fortressLabels.h"
#include "verticalLineLabels.h"
#include "horizontalLabels.h"
#include "teamSignalLabels.h"
#include "iDialogChain.h"
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
const int OFFSET_Y = 3;
const int SPACE_LABEL_SIZE_X = 3;
const int SPACE_LABEL_SIZE_Y = 1;

const FColor BLACK_BG = FColor::Black;
const FColor FOCUS_BLACK_BG = FColor::Grey50;
const FColor POTENTIAL_BLACK_BG = FColor::DeepPink6;
const FColor POTENTIAL_GENERAL_BLACK_BG = FColor::DarkCyan2;

const FColor RED_BG = FColor::Red;
const FColor FOCUS_RED_BG = FColor::Red1;
const FColor POTENTIAL_RED_BG = FColor::LightPink4;
const FColor POTENTIAL_GENERAL_RED_BG = FColor::LightCyan3;

const FColor NOTEAM_BG = FColor::Grey93;

class BoardDialog: public IDialogChain {
public:
    friend class MoveManager;
    explicit BoardDialog(FDialog* parent);
    void initLayout() override;
    void clickedCallback();
    void moveCallback();
    void dispatchChessmanMove(Point* source, Point* destination);
    void redrawTeamSignal();

    MoveManager* moveManager;
    void initHook() override;
private:
    void addCallback(ILabel* label, std::string event);
    IBoard* board;
    RiverBorderLabels riverBoundaryLabels{this};
    FortressLabels fortressLabels{this};
    VerticleLineLabels verticleLineLabels{this};
    HorizontalLineLabels horizontalLineLabels{this};
    TeamSignalLabels *teamSignalLabels;
    // DebugLabel debugLabel{this};
    ILabel* pieces[BOARD_WIDTH][BOARD_LENGTH];
};