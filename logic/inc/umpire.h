#include "utils.h"
#include "iChessman.h"
#include "iBoard.h"


class Umpire {

public:
    Umpire();
    bool preCheckMate(Point* from, Point* to);
    bool preCheckMate(Point* from, Point* to, team_code team);
    std::vector<Point*> checkMate(void);
    std::vector<Point*> checkMate(team_code team);
    std::vector<Point*> processCheckMate(team_code team);
private:
    IBoard *mBoard;
    void setBoard(IBoard* board);
    
};