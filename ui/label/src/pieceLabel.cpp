#include "pieceLabel.h"
#include "iBoard.h"
#include "board.h"
#include "iChessman.h"
#include "boardDialog.h"
#include "ITurn.h"
#include "log.h"

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

    IChessman* chessman = Board::getInstance()->getChessman(pos);
    team_code this_team = chessman->getTeam();

    if (event->getButton() == MouseButton::Left) {
        if (target) {
            boardDialog->setDestPoint(pos);
            LOG_F("This chessman is moved to %s", pos->to_string().c_str());
            LOG_F("%s at %s is captured", chessman->getName().c_str(), pos->to_string().c_str());
            emitCallback("move");
        } else if (ITurn::isSatisfiedTurn(this_team)) {
            boardDialog->setSourcePoint(pos);
            LOG_F("%s at %s is clicked", chessman->getName().c_str(), pos->to_string().c_str());
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