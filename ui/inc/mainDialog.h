#pragma once
#include "final/final.h"
#include "introDialog.h"
#include "boardDialog.h"

using namespace finalcut;

#define MAIN_DIALOG_POINT FPoint{1,1}
#define WINDOW_WIDTH 46
#define WINDOW_LENGTH 26
#define WINDOW_SIZE FSize{WINDOW_WIDTH, WINDOW_LENGTH}

class MainDialog : public FDialog {
public:
    explicit MainDialog(FWidget* = nullptr);

    void initLayout() override;
private:
    IntroDialog *introDialog;
    BoardDialog *boardDialog;
};