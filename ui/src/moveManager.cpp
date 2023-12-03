#include "moveManager.h"
#include "spaceLabel.h"

MoveManager::MoveManager(BoardDialog *boardDialog){
    board = Board::getInstance();
    this->mainDialog = boardDialog;
};


void MoveManager::setSourcePoint(Point* clicked) {
    source = clicked;
}
Point* MoveManager::getSourcePoint() {
    return source;
}

void MoveManager::setDestPoint(Point* to) {
    LOG_F("Set dest point %s", to->to_string());
    dest = to;
}
Point* MoveManager::getDestPoint() {
    return dest;
}

void MoveManager::movePiece() {
    ILabel* toPiece = mainDialog->pieces[dest->getX()][dest->getY()];
    ILabel* fromPiece = mainDialog->pieces[source->getX()][source->getY()];
    if (dynamic_cast<SpaceLabel*>(toPiece) != nullptr) {
        // If toPiece is a space label, we swap to labels
        fromPiece->changePosition(dest);
        toPiece->changePosition(source);

        // Swap the pieces in pieces array of the board dialog
        mainDialog->pieces[source->getX()][source->getY()] = toPiece;
        mainDialog->pieces[dest->getX()][dest->getY()] = fromPiece;

    } else {
        // If toPiece is a piece label, we delete the destined piece label
        // (considered as eliminated), move the source piece label and
        // create a space label where the source piece label was located.
        fromPiece->changePosition(dest);
        toPiece->changePosition(source);
        toPiece->hide();

        delete toPiece;
        // Create a new space label and assign all necessary functionalities
        mainDialog->pieces[dest->getX()][dest->getY()] = fromPiece;
        ILabel* newLabel = new SpaceLabel{mainDialog, source};
        mainDialog->pieces[source->getX()][source->getY()] = newLabel;
        newLabel->show();
        mainDialog->addCallback(newLabel, "move");
    }

    // Inform the board about the changes.
    board->move(source, dest);
}

void MoveManager::decorateTargetedPieces(bool value) {
    for (Point* point : possibleMoves) {
        if (value) {  
            mainDialog->pieces[point->getX()][point->getY()]->setTarget();
        } else {
            mainDialog->pieces[point->getX()][point->getY()]->unsetTarget();
        }
    }
}

void MoveManager::calculatePossibleMoves() {
    decorateTargetedPieces(false);
    possibleMoves = board->getPossibleMoves(source);
    decorateTargetedPieces(true);
}