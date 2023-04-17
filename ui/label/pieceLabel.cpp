#include "ui/label/pieceLabel.h"
#include "logic/iBoard.h"
#include "logic/board.h"
#include "logic/iChessman.h"
#include "ui/BoardDialog.h"

PieceLabel::~PieceLabel() {}

void PieceLabel::initLayout() {
    IBoard* board = Board::getInstance();
    int x = this->pos->getX();
    int y = this->pos->getY();
    IChessman* chessman = board->getChessman(x, y);

    team_code team = chessman->getTeam();
    if (target) {
        setBackgroundColor(team == BLACK ? FOCUS_BLACK_BG : FOCUS_RED_BG);
    } else {
        setBackgroundColor(team == BLACK ? BLACK_BG : RED_BG);
    }
    setText(chessman->getName());
    setForegroundColor(FColor::White);
    setBold();

    front();
    setGeometry(
        FPoint{x*SPACE_BW_PIECE_X+OFFSET_X, y*SPACE_BW_PIECE_Y+OFFSET_Y},
        FSize{PIECE_SIZE_X,PIECE_SIZE_Y}
    );

    FLabel::initLayout();
}

void PieceLabel::onMouseDown(FMouseEvent* event) {
    BoardDialog* boardDialog = (BoardDialog*) getParent();

    if (event->getButton() == MouseButton::Left) {
        if (target) {
            boardDialog->setToPoint(pos);
            emitCallback("move");
        } else {
            boardDialog->setClickedPoint(pos);
            emitCallback("clicked");
        }

    }
}

void PieceLabel::setTarget() {
    target = true;
    IBoard* board = Board::getInstance();
    int x = this->pos->getX();
    int y = this->pos->getY();
    IChessman* chessman = board->getChessman(x, y);

    team_code team = chessman->getTeam();
    setBackgroundColor(team == BLACK ? FOCUS_BLACK_BG : FOCUS_RED_BG);
    setForegroundColor(FColor::Black);
    redraw();
}

void PieceLabel::unsetTarget() {
    target = false;
    IBoard* board = Board::getInstance();
    int x = this->pos->getX();
    int y = this->pos->getY();
    IChessman* chessman = board->getChessman(x, y);

    team_code team = chessman->getTeam();
    setBackgroundColor(team == BLACK ? BLACK_BG : RED_BG);
    setForegroundColor(FColor::White);
    redraw();
}

void PieceLabel::changePosition(Point* to) {
    pos = to;
    setGeometry(
        FPoint{to->getX()*SPACE_BW_PIECE_X+OFFSET_X, to->getY()*SPACE_BW_PIECE_Y+OFFSET_Y},
        FSize{PIECE_SIZE_X,PIECE_SIZE_Y}
    );
    redraw();
}