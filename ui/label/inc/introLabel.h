#pragma once
#include "final/final.h"
#include <string>
#include <map>

using namespace finalcut;

class IntroLabel {
    public:
    explicit IntroLabel(FWidget* parent);
    void setColor();
    void togglePressKey();
    void toggleBars();

    private:
    static const int MAX_TILE_LENGTH = 20;
    static const int MAX_TILE_WIDTH = 40;
    static const int ENDGAME_LABEL_OFFSET_X = 3;
    static const int ENDGAME_LABEL_OFFSET_Y = 2;
    static const int PRESS_ANY_X_OFFSET = 11;
    static const int GRADIENT_MAX = 8;
    static const int GRADIENT_WIDTH = 3;
    static std::string PRESS_KEY;

    void setGradientBackground(FLabel *label, char code, int x, int y);
    FLabel* tiles[MAX_TILE_LENGTH][MAX_TILE_WIDTH];
    FLabel* pressKey;
    FLabel* lowerBar;
    FLabel* upperBar;
    static std::u16string intro[MAX_TILE_LENGTH];
    static std::string bg[MAX_TILE_LENGTH];
    static std::string fg[MAX_TILE_LENGTH];
    static FColor gradientColors[GRADIENT_MAX];
    static int gradientIndex;
};