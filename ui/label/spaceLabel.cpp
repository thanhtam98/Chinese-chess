#include "ui/label/spaceLabel.h"
#include "logic/iBoard.h"
#include "logic/board.h"
#include "logic/iChessman.h"
#include "ui/BoardDialog.h"
#include <string>

void SpaceLabel::initLayout() {
    IBoard* board = Board::getInstance();
    int x = pos->getX();
    int y = pos->getY();
    IChessman* chessman = board->getChessman(x, BOARD_LENGTH - y -1);

    if (target) {
        setBackgroundColor(FColor::Grey93);
    } else {
        setBackgroundColor(FColor::White);
    }
    setText(getCrossText());
    setForegroundColor(FColor::Black);

    front();
    setGeometry(
        FPoint{x*SPACE_BW_PIECE_X+OFFSET_X, y*SPACE_BW_PIECE_Y+OFFSET_Y},
        FSize{PIECE_SIZE_X,PIECE_SIZE_Y}
    );

    FLabel::initLayout();
}

std::string SpaceLabel::getCrossText() {
    int x = pos->getX();
    int y = pos->getY();
    char up = 1, down = 1, left = 1, right = 1;

    if (x == 0) left = 0;
    if (x == BOARD_WIDTH-1) right = 0;
    if (y == 0 || (y == BOARD_LENGTH/2 && x != 0 && x != BOARD_WIDTH-1)) 
        up = 0;
    if (y == BOARD_LENGTH-1 || (y == BOARD_LENGTH/2-1 &&
        x != 0 && x != BOARD_WIDTH-1)) 
        down = 0;

    CrossChar crossChar = { .bits{up, down, right, left} };
    std::string text;
    switch (crossChar.value)
    {
    case NON_LEFT:
        text = "├─";
        break;
    
    case NON_RIGHT:
        text = "┤ ";
        break;

    case NON_UP:
        text = "┬─";
        break;

    case NON_DOWN:
        text = "┴─";
        break;

    case NON_LEFT_RIGHT:
        text = "──";
        break;

    case NON_LEFT_DOWN:
        text = "└─";
        break;

    case NON_LEFT_UP:
        text = "┌─";
        break;

    case NON_RIGHT_DOWN:
        text = "┘ ";
        break;

    case NON_RIGHT_UP:
        text = "┐ ";
        break;

    case FULL:
        text = "┼─";
        break;

    default:
        text = "  ";
        break;
    }
    return text;
}

void SpaceLabel::setTarget() {
    target = true;
    setBackgroundColor(FColor::LightGray);
    redraw();
}

void SpaceLabel::unsetTarget() {
    target = false;
    setBackgroundColor(FColor::White);
    redraw();
}

void SpaceLabel::onMouseDown(FMouseEvent* event) {
    BoardDialog* boardDialog = (BoardDialog*) getParent();

    if (event->getButton() == MouseButton::Left) {
        if (target) {
            boardDialog->setToPoint(pos);
            emitCallback("move");
        }
    }
}

void SpaceLabel::changePosition(Point* to) {
    pos = to;
    setGeometry(
        FPoint{to->getX()*SPACE_BW_PIECE_X+OFFSET_X, to->getY()*SPACE_BW_PIECE_Y+OFFSET_Y},
        FSize{PIECE_SIZE_X,PIECE_SIZE_Y}
    );
    setText(getCrossText());
    redraw();
}