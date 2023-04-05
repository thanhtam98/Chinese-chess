#include "final/final.h"
#include "logic/iBoard.h"
#include "utils/constant.h"

using namespace finalcut;

class BoardDialog : public FDialog {
private:
    IBoard* board;
    FButton* pieces[BOARD_LENGTH][BOARD_WIDTH];
    void mapFromBoard();

public:
    explicit BoardDialog(FWidget* = nullptr);
    const FColor BLACK_BG = FColor::Black;
    const FColor FOCUS_BLACK_BG = FColor::Grey50;
    const FColor RED_BG = FColor::Red;
    const FColor FOCUS_RED_BG = FColor::LightRed;

    void initLayout() override;
};