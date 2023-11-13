#include "utils.h"
#include "iChessman.h"
#include "iBoard.h"

class umpire {

public:
    umpire(IBoard *board);

    std::vector<Point*> checkMate(team_code team);
private:
    IBoard *mBoard;
    
};