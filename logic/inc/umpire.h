#include "utils.h"
#include "iChessman.h"
#include "iBoard.h"

class Umpire {

public:
    Umpire(IBoard *board);
    std::vector<Point*> checkMate(void);
    std::vector<Point*> checkMate(team_code team);
private:
    IBoard *mBoard;
    
};