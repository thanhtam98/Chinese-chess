#include "introLabel.h"
#include <codecvt>

std::u16string IntroLabel::intro[] = {
u"                               ▄       ",
u"                              ▄█▙      ",
u"      █▄  ▄          ▐▄▖       ▜█      ",
u"     ▗██▟██▙▖        ▝██  ▗    ▐▌      ",
u"    ▗█▀ ▗██▘          █▌  ▐█▙  ▐▌      ",
u"   ▞▀   ▟█▘ ▗▄        █▌   ██  ▐▌      ",
u"  ▗▄▄▟█▜▛▀▀▀▀▜█▌      █▌   █▌  ▐▙▄▄    ",
u"  ▝█▌  ▐██  ▚▐█▀   ▗▄▄█▞▛ ▄█▙███▛▀▘    ",
u"   ▜▌  ▟▟▀▘▟▜▛ ▀█▀▐▌█▚▛█▜▙▐▗▛▀ ▐▌      ",
u"   ▐▛▀██▜▄▖▜▟▘  █ ▝▙▛▝▙▛▐▝█▝▙█▄▐▌      ",
u"  ▗▛▀▀▀▛▀▌▛▀▛▀▀▀▛▀▙▛▀▛▀▀▀▀█▀▀▀▀▛▀▀▀▀▌  ",
u"  ▛ ▗▄▄▌ █▌ ▙▖ ▄▌ ▝▌ ▌ ▄▄▄▌ ▄▄▄▌ ▄▄▄▌  ",
u"  ▌ █ ▄▌    █▌ ▌▌ ▖  ▌  ▐ ▙   ▝▌   ▙▄▖ ",
u"  ▙ ▝▀▀▌ █▌ ▛▘ ▀▌ █▖ ▌ ▀▀▀▛▀▀▘ ▌ ▀▀▀█▙ ",
u"  ▟▙▄▄▄▙▄█▙▄▙▄▄▄▙▄▙▙▄▙▄▄▄▄▙▄▄▄▟▙▄▄▄▄▌  ",
u" ▀▘  ▗▄▀   ▌ ▌▌ ▌    ▛    ▛    ▌▜▄▄    ",
u"   ▗▄▛▌ ▟▀█▌ ▀▘ ▌ ▀▜▀▌ ▀▀▜▌ ▀▀▜▌▝██▙▖  ",
u" ▗▟▀▘ ▌ ▜██▌ ▄▖ ▌ ▄▟▄█▄▄▖ █▄▄▖ ▌ ▝▀██▌ ",
u"▝▀    ▀▄   ▌ ▌▌ ▌    ▌   ▗▌   ▗▌    ▀▀ ",
u"       ▝▀▀▀▀▀▘▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀        "
// u"           ▝▀         ▀▘               ",
// u"        ▟▀▘▟▜▛ ▀█▀▐▌█▚▛█▜▙▐▗▛▀         ",
// u"        ▜▄▖▜▟▘  █ ▝▙▛▝▙▛▐▝█▝▙█         "
};

std::string IntroLabel::bg[] = {
"                                       ",
"                                       ",
"                                       ",
"                                       ",
"                                       ",
"                                       ",
"                                       ",
"                                       ",
"                                       ",
"                                       ",
"   112233 43322110 11223344332211001   ",
"  1122334 33221100112233443322110011   ",
"  12   44332 11 011223344 322110011    ",
"  2233443 22110011 23344332211001122   ",
"   334433221100112 33443322110011223   ",
"       322110 11223344332211001        ",
"      322  001122334 3322110011        ",
"      221  011223344 3221100112        ",
"       110011 23344332211001122        ",
"                                       "
// "                                       ",
// "                                       ",
// "                                       ",
};

std::string IntroLabel::fg[] = {
"                               1       ",
"                              111      ",
"      11  1          111       11      ",
"     11111111        111  1    11      ",
"    111 1111          11  111  11      ",
"   11   111 11        11   11  11      ",
"  11111111111111      11   11  1111    ",
"  111  111  2111   111121 111111111    ",
"   11  12222222222222222222222 11      ",
"   111112222222222222222222222111      ",
"                                       ",
"                                       ",
"      1                             11 ",
"                                     1 ",
"                                       ",
" 11  1                          1111   ",
"   111                          11111  ",
" 1111                            11111 ",
"11                                  11 ",
"                                       "
// "                                       ",
// "                                       ",
// "                                       "
};

std::string IntroLabel::PRESS_KEY = "PRESS ANY KEY";

FColor IntroLabel::gradientColors[] = {
    FColor::White, FColor::Yellow1, FColor::Yellow, FColor::Orange1, 
    FColor::Orange2, FColor::Orange1, FColor::Yellow, FColor::Yellow1};

int IntroLabel::gradientIndex = 0;

IntroLabel::IntroLabel(FWidget* parent) {
    std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> converter;

    for (int i = 0; i < MAX_TILE_LENGTH; i++) {
        for (int j = 0; j < MAX_TILE_WIDTH; j++) {
            FLabel* label = new FLabel{parent};
            std::string ch = converter.to_bytes(intro[i].substr(j, 1));
            label->setText(ch);
            setGradientBackground(label, bg[i][j], i, j);
            if (fg[i][j] == '1') {
                label->setForegroundColor(FColor::DarkRed2);
            } else if (fg[i][j] == '2') {
                label->setForegroundColor(FColor::Black);
            }
            label->setGeometry(
                FPoint{ENDGAME_LABEL_OFFSET_X+j, ENDGAME_LABEL_OFFSET_Y+i},
                FSize{1, 1}
            );
            tiles[i][j] = label;
        }
    }

    upperBar = new FLabel{parent};
    upperBar->setText("████████████████████████████████████████████");
    upperBar->setForegroundColor(FColor::Red);
    upperBar->setGeometry(
        FPoint{0, 0},
        FSize{46, 1}
    );

    lowerBar = new FLabel{parent};
    lowerBar->setText("████████████████████████████████████████████");
    lowerBar->setForegroundColor(FColor::Red);
    lowerBar->setGeometry(
        FPoint{0, ENDGAME_LABEL_OFFSET_Y + MAX_TILE_LENGTH + 1},
        FSize{46, 1}
    );

    pressKey = new FLabel{parent};
    pressKey->setText(PRESS_KEY);
    pressKey->setForegroundColor(FColor::Black);
    pressKey->setGeometry(
        FPoint{
            PRESS_ANY_X_OFFSET,
            ENDGAME_LABEL_OFFSET_Y + MAX_TILE_LENGTH,
        },
        FSize{13, 1}
    );
}

void IntroLabel::setGradientBackground(FLabel *label, char code, int x, int y) {
    if (code != ' ') {
        int gIndex = ((x + y + gradientIndex) / GRADIENT_WIDTH ) % GRADIENT_MAX;
        label->setBackgroundColor(gradientColors[gIndex]);
        label->setForegroundColor(FColor::Black);
    }
}

void IntroLabel::setColor() {
    gradientIndex++;
    for (int i = 0; i < MAX_TILE_LENGTH; i++) {
        for (int j = 0; j < MAX_TILE_WIDTH; j++) {
            FLabel* label = tiles[i][j];
            FColor curColor = label->getBackgroundColor();
            setGradientBackground(label, bg[i][j], i, j);
        }
    }
}

void IntroLabel::togglePressKey() {
    static bool toggleStatus = true;
    if (toggleStatus) {
        pressKey->hide();
    } else {
        pressKey->show();
    }
    toggleStatus = (toggleStatus == false);
}

void IntroLabel::toggleBars() {
    static FColor color = FColor::Black;
    upperBar->setForegroundColor(color);
    lowerBar->setForegroundColor(color);
    color = (color == FColor::Black) ? FColor::Red : FColor::Black;
}