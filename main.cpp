#include <iostream>
#include "final/final.h"
#include "ui.h"
#include "constant.h"
#include "point.h"
#include "rule.h"
#include "iBoard.h"
#include "board.h"
#include "mainDialog.h"
#include "log.h"

using namespace std;
using namespace finalcut;

auto main (int argc, char* argv[]) -> int
{
  // freopen("/workspaces/chinese-chess/log.txt","w",stdout);
  // cout<<"Start the logfile" << endl;
  string str = "Alo!";
  LOG_F("Start the game %s", str.c_str());
  FApplication app{argc, argv};

  // Force terminal initialization without calling show()
  app.initTerminal();

  // The following lines require an initialized terminal
  if ( finalcut::FTerm::canChangeColorPalette() )
    app.setBackgroundColor(FColor::Default);

  MainDialog board{&app};

  board.setGeometry(FPoint{1, 1}, FSize{46, 26}, false);

  // Set dialog object mouse_draw as main widget
  FWidget::setMainWidget(&board);

  // Show and start the application
  board.show();
  return app.exec();
}