#include "final/final.h"
#include "logic/iBoard.h"
#include "utils/constant.h"
#include "ui/label/ILabel.h"
#include "ui/label/riverBorderLabels.h"
#include "ui/label/fortressLabels.h"
#include "ui/label/verticalLineLabels.h"
#include "ui/label/horizontalLabels.h"
#include "ui/label/debugLabel.h"
#include "utils/point.h"
#include <vector>

using namespace finalcut;

const int PIECE_SIZE_X = 2;
const int PIECE_SIZE_Y = 1;
const int SPACE_SIZE_X = 3;
const int SPACE_SIZE_Y = 1;
const int SPACE_BW_PIECE_X = PIECE_SIZE_X + SPACE_SIZE_X;
const int SPACE_BW_PIECE_Y = PIECE_SIZE_Y + SPACE_SIZE_Y;
const int OFFSET_X = 2;
const int OFFSET_Y = 1;
const int SPACE_LABEL_SIZE_X = 3;
const int SPACE_LABEL_SIZE_Y = 1;
const FColor BLACK_BG = FColor::Black;
const FColor FOCUS_BLACK_BG = FColor::Grey50;
const FColor RED_BG = FColor::Red;
const FColor FOCUS_RED_BG = FColor::Red1;

class BoardDialog : public FDialog {
public:
    explicit BoardDialog(FWidget* = nullptr);

    void initLayout() override;
    void setClickedPoint(Point* clicked);
    Point* getClickedPoint();
    void setToPoint(Point* to);
    Point* getToPoint();
private:
    void setValueForTargetedPieces(bool value);
    void clickedCallback();
    void moveCallback();
    void swapPieces();

    IBoard* board;
    RiverBorderLabels riverBoundaryLabels{this};
    FortressLabels fortressLabels{this};
    VerticleLineLabels verticleLineLabels{this};
    HorizontalLineLabels horizontalLineLabels{this};
    DebugLabel debugLabel{this};
    ILabel* pieces[BOARD_WIDTH][BOARD_LENGTH];

    Point* clickedPoint;
    Point* toPoint;
    vector<Point*> possibleMoves;
};