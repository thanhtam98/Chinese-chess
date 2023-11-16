#include "spaceLabel.h"
#include "iBoard.h"
#include "board.h"
#include "iChessman.h"
#include "mainDialog.h"
#include <string>
#include "log.h"
#include "moveManager.h"

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
    char up = 1, down = 1, left = 1, right = 1, asterisk = 0;

    if (x == 0) left = 0;
    if (x == BOARD_WIDTH-1) right = 0;
    if (y == 0 || (y == BOARD_LENGTH/2 && x != 0 && x != BOARD_WIDTH-1)) 
        up = 0;
    if (y == BOARD_LENGTH-1 || (y == BOARD_LENGTH/2-1 &&
        x != 0 && x != BOARD_WIDTH-1)) 
        down = 0;
    
    if ((y == 2 || y == 7) && (x == 1 || x == 7)) asterisk = 1;
    if ((y == 3 || y == 6) && (x == 0 || x == 2 || x == 4 || x == 6 || x == 8))
        asterisk = 1;

    CrossChar crossChar = { .bits{up, down, right, left, asterisk} };
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

    case FULL_ASTERISK:
        text = "╬─";
        break;

    case NON_LEFT_ASTERISK:
        text = "╠─";
        break;

    case NON_RIGHT_ASTERISK:
        text = "╣ ";
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

void SpaceLabel::setPotential() {
    target = true;
    setBackgroundColor(FColor::LightRed);
    redraw();
}

void SpaceLabel::unsetTarget() {
    target = false;
    setBackgroundColor(FColor::White);
    redraw();
}

void SpaceLabel::onMouseDown(FMouseEvent* event) {
    MainDialog* boardDialog = (MainDialog*) getParent();

    if (event->getButton() == MouseButton::Left) {
        if (target) {
            boardDialog->moveManager->setDestPoint(pos);
            LOG_F("This chessman is moved to %s", pos->to_string().c_str());
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