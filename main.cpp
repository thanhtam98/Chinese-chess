#include <iostream>
#include "final/final.h"
#include "ui/ui.h"
#include "utils/constant.h"
#include "utils/point.h"
#include "rule/rule.h"
#include "logic/iBoard.h"
#include "logic/board.h"
#include "ui/BoardDialog.h"

using namespace std;
using namespace finalcut;

auto main (int argc, char* argv[]) -> int
{
  // freopen("/workspaces/chinese-chess/log.txt","w",stdout);
  // cout<<"Start the logfile" << endl;

  FApplication app{argc, argv};

  BoardDialog board{&app};

  board.setGeometry(FPoint{1, 1}, FSize{50, 22}, false);

  // Set dialog object mouse_draw as main widget
  FWidget::setMainWidget(&board);

  // Show and start the application
  board.show();
  return app.exec();
}