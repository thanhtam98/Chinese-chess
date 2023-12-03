#include "moveManager.h"
#include "spaceLabel.h"
#include "mainDialog.h"
#include "ITurn.h"
#include "board.h"

MoveManager::MoveManager(BoardDialog *boardDialog){
    board = Board::getInstance();
    this->mainDialog = boardDialog;
    umpire = new Umpire();
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

/**
 * On each movement, we need to check if:
 *  - The movement will make the opponent/partner general being targetted; or
 *  - The movement will make the opponent/partner general being discharged.
 * 
*/

bool MoveManager::preCalculatePossiblePotentials(){
    IChessman* chessman = board->getChessman(source);
    team_code team = chessman->getTeam();
    // auto result = umpire->checkMate(team);

    // if (result.size() == 0){
    //     /* General is not targetted. Check if the next movement is self-destroying  */
    //     if (umpire->preCheckMate(source, dest, team) == true){
    //         return false;
    //     }
    //     return true;
    // }   
    // else {
    //     /* Gereral is targetted. Check if the next movement can discharge*/
    //     if (umpire->preCheckMate(source, dest, team) == true){
    //         return false;
    //     }
    //     return true;
    // }    
    return !umpire->preCheckMate(source, dest, team);
}
void MoveManager::movePiece() {

    /* pre check*/
    if (preCalculatePossiblePotentials() == false){
        return;
    }
    

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
    calculatePossiblePotentials();
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
void MoveManager::decoratePotentialPieces(bool value) {
    for (Point* point : possiblePotentials) {
        if (value) {  
            mainDialog->pieces[point->getX()][point->getY()]->setPotential();
        } else {
            mainDialog->pieces[point->getX()][point->getY()]->unsetTarget();
        }
    }

    if (!value){
        mainDialog->pieces[board->getGeneralLocation(RED)->getX()]
                            [board->getGeneralLocation(RED)->getY()]->unsetTarget();
        mainDialog->pieces[board->getGeneralLocation(BLACK)->getX()]
                            [board->getGeneralLocation(BLACK)->getY()]->unsetTarget();
    }
}
void MoveManager::calculatePossibleMoves() {
    decorateTargetedPieces(false);
    possibleMoves = board->getPossibleMoves(source);
    decorateTargetedPieces(true);
}

void MoveManager::calculatePossiblePotentials(){
    decoratePotentialPieces(false);
    possiblePotentials = umpire->checkMate();
    decoratePotentialPieces(true);

}