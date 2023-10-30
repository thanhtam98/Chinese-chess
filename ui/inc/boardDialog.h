#include "final/final.h"
#include "iBoard.h"
#include "constant.h"
#include "ILabel.h"
#include "riverBorderLabels.h"
#include "fortressLabels.h"
#include "verticalLineLabels.h"
#include "horizontalLabels.h"
#include "debugLabel.h"
#include "point.h"
#include "teamSignalLabels.h"
#include <vector>

using namespace finalcut;

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

class BoardDialog : public FDialog {
public:
    explicit BoardDialog(FWidget* = nullptr);

    void dispatchChessmanMove(Point* source, Point* destination);
    void initLayout() override;
    void setSourcePoint(Point* source);
    Point* getSourcePoint();
    void setDestPoint(Point* dest);
    Point* getDestPoint();
private:
    // Set/ Unset to draw/ re-draw possible moves with different colors
    void setValueForTargetedPieces(bool value);
    void clickedCallback();
    void moveCallback();
    void swapPieces();

    IBoard* board;
    RiverBorderLabels riverBoundaryLabels{this};
    FortressLabels fortressLabels{this};
    VerticleLineLabels verticleLineLabels{this};
    HorizontalLineLabels horizontalLineLabels{this};
    TeamSignalLabels *teamSignalLabels;
    DebugLabel debugLabel{this};
    ILabel* pieces[BOARD_WIDTH][BOARD_LENGTH];

    Point* sourcePoint;
    Point* destPoint;
    vector<Point*> possibleMoves;
};