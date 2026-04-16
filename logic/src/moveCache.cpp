#include "moveCache.h"
#include <set>
#include "board.h"

MoveCache* MoveCache::instance = nullptr;
MoveCache* MoveCache::getInstance() {
    if (instance == nullptr) {
        instance = new MoveCache();
    }
    return instance;
}

void MoveCache::fillPossibleMoves(IChessman* owner, vector<Point*> moves) {
    for (Point* point : moves) {
        map[point->getX()][point->getY()].insert(owner);
    }
    this->chessmenMap[owner] = moves;
}

void MoveCache::removePossibleMoves(IChessman* owner) {
    auto moves = this->chessmenMap[owner];
    for (Point* point : moves) {
        auto set = map[point->getX()][point->getY()].erase(owner);
    }
}

std::set<IChessman*> MoveCache::effectedChessmenAt(Point* point) {
    return map[point->getX()][point->getY()];
}

std::set<IChessman*> MoveCache::effectedChessmenByTeam(Point* point, team_code team) {
    std::set<IChessman*> result;
    for (auto chessman : map[point->getX()][point->getY()]) {
        if (chessman->getTeam() == team) {
            result.insert(chessman);
        }
    }
    return result;
}

std::set<IChessman*> MoveCache::effectedChessmenAt(int x, int y) {
    if (!Point::isWithinBoundary(x, y)) return {};
    return map[x][y];
}

std::vector<Point*> MoveCache::getPossibleMoves(IChessman* owner) {
    return this->chessmenMap[owner];
}

void MoveCache::dumpCache() {
    auto board = Board::getInstance();
    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_LENGTH; y++) {
            auto chessman = board->getChessman(x, y);
            if (chessman != nullptr) {
                auto moves = this->getPossibleMoves(chessman);
                std::string log = "";
                for (auto point : moves) {
                    log += point->to_string() + ", ";
                }
                LOG_F("%s can move to %s", chessman->getName().c_str(), log.c_str());
            }
            auto set = this->effectedChessmenAt(x, y);
            if (!set.empty()) {
                std::string log = "";
                for (auto chessman : set) {
                    log += chessman->getName() + ", ";
                }
                LOG_F("Point [%d;%d] are considered by %s", x, y, log.c_str());
            }
        }
    }
}

void MoveCache::clearAndRecalculate() {
    
}