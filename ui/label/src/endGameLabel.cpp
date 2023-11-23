#include "endGameLabel.h"
#include "log.h"
#include <iostream>
#include <codecvt>

std::u16string EndGameLabel::gameOver[] = {
u" ██████╗   █████╗  ███╗   ███╗ ███████╗ ",
u"██╔════╝  ██╔══██╗ ████╗ ████║ ██╔════╝ ",
u"██║  ███╗ ███████║ ██╔████╔██║ █████╗   ",
u"██║   ██║ ██╔══██║ ██║╚██╔╝██║ ██╔══╝   ",
u"╚██████╔╝ ██║  ██║ ██║ ╚═╝ ██║ ███████╗ ",
u" ╚═════╝  ╚═╝  ╚═╝ ╚═╝     ╚═╝ ╚══════╝ ",
u"  ██████╗  ██╗   ██╗ ███████╗ ██████╗   ",
u" ██╔═══██╗ ██║   ██║ ██╔════╝ ██╔══██╗  ",
u" ██║   ██║ ██║   ██║ █████╗   ██████╔╝  ",
u" ██║   ██║ ╚██╗ ██╔╝ ██╔══╝   ██╔══██╗  ",
u" ╚██████╔╝  ╚████╔╝  ███████╗ ██║  ██║  ",
u"  ╚═════╝    ╚═══╝   ╚══════╝ ╚═╝  ╚═╝  "
};

std::u16string EndGameLabel::youWin[] = {
u"     ██╗   ██╗  ██████╗  ██╗   ██╗      ",
u"     ╚██╗ ██╔╝ ██╔═══██╗ ██║   ██║      ",
u"      ╚████╔╝  ██║   ██║ ██║   ██║      ",
u"       ╚██╔╝   ██║   ██║ ██║   ██║      ",
u"        ██║    ╚██████╔╝ ╚██████╔╝      ",
u"        ╚═╝     ╚═════╝   ╚═════╝       ",
u"     ██╗    ██╗ ██╗ ███╗   ██╗ ██╗      ",
u"     ██║    ██║ ██║ ████╗  ██║ ██║      ",
u"     ██║ █╗ ██║ ██║ ██╔██╗ ██║ ██║      ",
u"     ██║███╗██║ ██║ ██║╚██╗██║ ╚═╝      ",
u"     ╚███╔███╔╝ ██║ ██║ ╚████║ ██╗      ",
u"      ╚══╝╚══╝  ╚═╝ ╚═╝  ╚═══╝ ╚═╝      "
};

std::u16string EndGameLabel::youLose[] = {
u"     ██╗   ██╗  ██████╗  ██╗   ██╗      ",
u"     ╚██╗ ██╔╝ ██╔═══██╗ ██║   ██║      ",
u"      ╚████╔╝  ██║   ██║ ██║   ██║      ",
u"       ╚██╔╝   ██║   ██║ ██║   ██║      ",
u"        ██║    ╚██████╔╝ ╚██████╔╝      ",
u"        ╚═╝     ╚═════╝   ╚═════╝       ",
u"██╗       ██████╗  ███████╗ ███████╗ ██╗",
u"██║      ██╔═══██╗ ██╔════╝ ██╔════╝ ██║",
u"██║      ██║   ██║ ███████╗ █████╗   ██║",
u"██║      ██║   ██║ ╚════██║ ██╔══╝   ╚═╝",
u"███████╗ ╚██████╔╝ ███████║ ███████╗ ██╗",
u"╚══════╝  ╚═════╝  ╚══════╝ ╚══════╝ ╚═╝"
};

EndGameLabel::EndGameLabel(FWidget* parent) {
    for (int i = 0; i < MAX_TILE_WIDTH; i++) {
        for (int j = 0; j < MAX_TILE_LENGTH; j++) {
            tiles[i][j] = new FLabel{parent};
        }
    }
    LOG_F("Size %d * %d = %d", youLose->size(), youLose[0].size(), youLose->size() * youLose[0].size())
}

void EndGameLabel::show(EndGameText text, FColor bg, FColor fg) {
    std::u16string *content;
    std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> converter;
    switch (text) {
        case GAME_OVER:
            content = gameOver;
            break;
        case YOU_WIN:
            content = youWin;
            break;
        case YOU_LOSE:
            content = youLose;
            break;
        default:
            break;
    }
    for (int i = 0; i < MAX_TILE_LENGTH; i++) {
        for (int j = 0; j < MAX_TILE_WIDTH; j++) {
            FLabel* label = tiles[j][i];
            // std::cout << converter.to_bytes(content[i].substr(j, 1)) << std::endl;
            // std::ucout << content[i].substr(j, 3) << std::endl;
            std::string ch = converter.to_bytes(content[i].substr(j, 1));
            LOG_F("Char %s at %d; %d", ch.c_str(), i, j);
            label->setText(ch);
            if (ch.compare("█")) {
                label->setForegroundColor(fg);
            } else if (ch.compare(" ") != 0) {
                label->setForegroundColor(bg);
            }
            label->setGeometry(
                FPoint{ENDGAME_LABEL_OFFSET_X+j, ENDGAME_LABEL_OFFSET_Y+i},
                FSize{1, 1}
            );
        }
    }
}