#pragma once
#include "final/final.h"
#include <string>

using namespace finalcut;

enum EndGameText {
    GAME_OVER,
    YOU_WIN,
    YOU_LOSE
};

class EndGameLabel {
    public:
    explicit EndGameLabel(FWidget* parent);
    void show(EndGameText text, FColor fg = FColor::Black, FColor bg = FColor::Blue);

    private:
    static const int MAX_TILE_LENGTH = 12;
    static const int MAX_TILE_WIDTH = 40;
    static const int ENDGAME_LABEL_OFFSET_X = 3;
    static const int ENDGAME_LABEL_OFFSET_Y = 5;
    FLabel* tiles[MAX_TILE_WIDTH][MAX_TILE_LENGTH];
    static std::u16string gameOver[MAX_TILE_LENGTH];
    static std::u16string youWin[MAX_TILE_LENGTH];
    static std::u16string youLose[MAX_TILE_LENGTH];
};