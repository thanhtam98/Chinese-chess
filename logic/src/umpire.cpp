#include "umpire.h"
#include "iBoard.h"
#include "board.h"
Umpire::Umpire(){

    // mBoard = board;
}
void Umpire::setBoard(IBoard* board){
    mBoard = board;
}
bool Umpire::preCheckMate(Point* from, Point* to, team_code team){
    IBoard* snapshoot  = new Board(Board::getInstance());
   
    snapshoot->move(from, to);
    setBoard(snapshoot);

    auto result = processCheckMate(team);
    
    delete snapshoot;
    return result.size() != 0 ? true : false;
}

bool Umpire::preCheckMate(Point* from, Point* to){
    IBoard* snapshoot  = new Board(Board::getInstance());
    snapshoot->move(from, to);

    setBoard(snapshoot);

    auto red = processCheckMate(RED);
    auto black = processCheckMate(BLACK);
   
    delete snapshoot;
    return red.size() + black.size() != 0 ? true : false;

}


std::vector<Point*> Umpire::checkMate(void) {
    std::vector<Point*> ret;

    setBoard(Board::getInstance());
    
    auto red = processCheckMate(RED);
    auto black = processCheckMate(BLACK);

    ret.insert(ret.end(), red.begin(), red.end());
    ret.insert(ret.end(), black.begin(), black.end());
    return ret;
}

std::vector<Point*> Umpire::checkMate(team_code team) {
    std::vector<Point*> ret;

    setBoard(Board::getInstance());

    return processCheckMate(team);
}
/**
 * @brief check if the GENERAL of this team is being targeted.
*/
std::vector<Point*> Umpire::processCheckMate(team_code team){
   
    if (mBoard == nullptr)
        return {};
    
    std::vector<Point*> ret;
    /* Find where GENERAL is located */
    Point *generalLocation = mBoard->getGeneralLocation(team);
    IChessman *genernalChessman = mBoard->getChessman(generalLocation);
    /* Scan whole map */
    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_LENGTH; y++) {
            /* Get the chessman based on it's location */
            IChessman *chessman = mBoard->getChessman(x,y);
            
            if (chessman == nullptr) {
                continue;
            }
            /* Check if it is an oppment */
            if (chessman->getTeam() == genernalChessman->getTeam()){
                continue;
            }

            std::vector<Point*> possibleMoves = 
                chessman->getPossibleMoves(mBoard);
            
            if (std::find(possibleMoves.begin(), possibleMoves.end(),
                generalLocation) != possibleMoves.end()){
                ret.push_back(Point::of(x,y));
            }

        }
    }
    /* Also including GENERAL for clearly display*/
    if (ret.size() != 0){
        ret.push_back(generalLocation);
    }
    return ret;
}