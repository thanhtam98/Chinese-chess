#include "final/final.h"
#include "logic/iBoard.h"
#include "utils/constant.h"

using namespace finalcut;

class BoardDialog : public FDialog {
public:
    explicit BoardDialog(FWidget* = nullptr);
    const FColor BLACK_BG = FColor::Black;
    const FColor FOCUS_BLACK_BG = FColor::Grey50;
    const FColor RED_BG = FColor::Red;
    const FColor FOCUS_RED_BG = FColor::LightRed;
    static const int PIECE_SIZE_X = 4;
    static const int PIECE_SIZE_Y = 1;
    static const int SPACE_SIZE_X = 1;
    static const int SPACE_SIZE_Y = 1;
    static const int SPACE_BW_PIECE_X = PIECE_SIZE_X + SPACE_SIZE_X;
    static const int SPACE_BW_PIECE_Y = PIECE_SIZE_Y + SPACE_SIZE_Y;
    static const int OFFSET_X = 1;
    static const int OFFSET_Y = 1;
    static const int SPACE_LABEL_SIZE_X = 1;
    static const int SPACE_LABEL_SIZE_Y = 1;

    void initLayout() override;
private:
    IBoard* board;
    FLabel* riverBoundaryLabel;
    FLabel* horizontalLines[BOARD_WIDTH-1][BOARD_LENGTH];
    FLabel* verticalLines[BOARD_WIDTH][BOARD_LENGTH-1];
    FLabel* verticalLinesAtBorder[2];
    FLabel* fortressLines[2][4];
    FButton* pieces[BOARD_WIDTH][BOARD_LENGTH];

    void initChessmanFromBoard();
    void initOtherBoardItems();

};