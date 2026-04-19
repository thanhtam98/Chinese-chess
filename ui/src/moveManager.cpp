#include "moveManager.h"
#include "spaceLabel.h"
#include "mainDialog.h"
#include "ITurn.h"
#include "board.h"
#include "websockpp.h"
#include "configurator.h"

MoveManager::MoveManager(BoardDialog *boardDialog){
    board = Board::getInstance();
    this->mainDialog = boardDialog;
    umpire = new Umpire();
    
    ConnectionBase *con = ConnectionBase::getInstance();
    setConnectionInstance(con);
}

void MoveManager::setConnectionInstance(ConnectionBase *con){

    if (con != nullptr)
    {
        // con->run(); // Moved to configDialog.cpp
        this->transfer = new Transfer{con};
        this->transfer->setCallback(std::bind(&MoveManager::movePieceTransferCb, this,
                                              ::_1, ::_2),
                                    std::bind(&MoveManager::selPieceTransferCb, this,
                                              ::_1));
    }
}

void MoveManager::setSourcePoint(Point *clicked)
{
    source = clicked;
}
Point *MoveManager::getSourcePoint()
{
    return source;
}

void MoveManager::setDestPoint(Point* to) {
    LOG_F("Set dest point %s", to->to_string().c_str());
    dest = to;
}
Point *MoveManager::getDestPoint()
{
    return dest;
}
void MoveManager::selPieceTransferCb(Point *from)
{
    LOG_F("Sel Callback");
    setSourcePoint(from);
    calculatePossibleMoves(false);
}

/**
 * On each movement, we need to check if:
 *  - The movement will make the opponent/partner general being targetted; or
 *  - The movement will make the opponent/partner general being discharged.
 * 
*/

bool MoveManager::preCalculatePossiblePotentials(){
    LOG_F("Pre calculate possible potentials");
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

void MoveManager::movePieceTransferCb(Point *from, Point *to)
{
    LOG_F("Move Callback");
    setSourcePoint(from);
    setDestPoint(to);
    decorateTargetedPieces(false);
    movePiece(false);
    ITurn::end();
    mainDialog->redrawTeamSignal();
    // refresh possible move
}

bool MoveManager::movePiece(bool shouldNotify) {
    LOG_F("Move Piece");

    if (preCalculatePossiblePotentials() == false){
        LOG_F("Checkmate satisfied");
        return false;
    }

    ILabel* toPiece = mainDialog->pieces[dest->getX()][dest->getY()];
    ILabel* fromPiece = mainDialog->pieces[source->getX()][source->getY()];
    if (dynamic_cast<SpaceLabel*>(toPiece) != nullptr) {
        LOG_F("If toPiece is a space label, we swap to labels");
        fromPiece->changePosition(dest);
        toPiece->changePosition(source);

        LOG_F("Swap the pieces in pieces array of the board dialog");
        mainDialog->pieces[source->getX()][source->getY()] = toPiece;
        mainDialog->pieces[dest->getX()][dest->getY()] = fromPiece;
    }
    else
    {
        LOG_F("If toPiece is a piece label, we delete the destined piece label \
            (considered as eliminated), move the source piece label and create a \
            space label where the source piece label was located.");
        fromPiece->changePosition(dest);
        toPiece->changePosition(source);
        toPiece->hide();

        delete toPiece;
        LOG_F("create a new space label and assign all necessary functionalities");
        mainDialog->pieces[dest->getX()][dest->getY()] = fromPiece;
        ILabel *newLabel = new SpaceLabel{mainDialog, source};
        mainDialog->pieces[source->getX()][source->getY()] = newLabel;
        newLabel->show();
        mainDialog->addCallback(newLabel, "changed");
    }

    LOG_F("Inform the board about the changes.");
    board->move(source, dest);
    calculatePossiblePotentials();

    LOG_F("Notify MOV");
    if (shouldNotify) {
        transfer->sendMsg(MOV, source, dest);
    }

    return true;
}

void MoveManager::decorateTargetedPieces(bool value)
{
    for (Point *point : possibleMoves)
    {
        if (value)
        {
            mainDialog->pieces[point->getX()][point->getY()]->setTarget();
        }
        else
        {
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


void MoveManager::calculatePossiblePotentials(){
    decoratePotentialPieces(false);
    possiblePotentials = umpire->checkMate();
    decoratePotentialPieces(true);
}

void MoveManager::calculatePossibleMoves(bool shouldNotify)
{
    decorateTargetedPieces(false);
    possibleMoves = board->getPossibleMoves(source);
    decorateTargetedPieces(true);
    if (shouldNotify)
    {
        transfer->sendMsg(SEL, source);
    }
}