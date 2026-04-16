#pragma once
#include <set>
#include <unordered_map>
#include "utils.h"
#include "iChessman.h"

using namespace std;

class IChessman;

class MoveCache {
public:
    /* Singleton */
    static MoveCache* getInstance();

    void clearAndRecalculate();
    void fillPossibleMoves(IChessman* owner, vector<Point*> moves);
    void removePossibleMoves(IChessman* owner);
    std::vector<Point*> getPossibleMoves(IChessman* owner);
    std::set<IChessman*> effectedChessmenAt(Point* point);
    std::set<IChessman*> effectedChessmenByTeam(Point* point, team_code team);
    std::set<IChessman*> effectedChessmenAt(int x, int y);
    void dumpCache();
private:
    MoveCache() {};
    /* The single instance for Singleton */
    static MoveCache* instance;

    std::set<IChessman*> map[BOARD_WIDTH][BOARD_LENGTH];
    std::unordered_map<IChessman*, std::vector<Point*>> chessmenMap;
};