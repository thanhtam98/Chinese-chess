#include <cstring>
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>

#include "ui.h"
#include "utils.h"
#include "mainDialog.h"
#include "websockpp.h"
#include "configDialog.h"
#include "connectionBase.h"

using namespace std;
using namespace finalcut;

auto main (int argc, char* argv[]) -> int
{
  // freopen("/workspaces/chinese-chess/log.txt","w",stdout);
  // cout<<"Start the logfile" << endl;
  std::vector<char*> app_argv;
  app_argv.reserve(static_cast<size_t>(argc));
  app_argv.push_back(argv[0]);
  for (int i = 1; i < argc; ++i) {
    if (std::strcmp(argv[i], "-f") == 0) {
      if (i + 1 < argc) {
        Logger::setLogFilePath(argv[i + 1]);
        ++i;
      }
      continue;
    }
    app_argv.push_back(argv[i]);
  }
  int app_argc = static_cast<int>(app_argv.size());

  string str = "Alo!";
  LOG_F("Start the game %s", str.c_str());

  FApplication app{app_argc, app_argv.data()};

  // Force terminal initialization without calling show()
  app.initTerminal();

  // The following lines require an initialized terminal
  if ( finalcut::FTerm::canChangeColorPalette() )
    app.setBackgroundColor(FColor::Default);

  MainDialog board{&app};

  board.setGeometry(MAIN_DIALOG_POINT, WINDOW_SIZE, false);

  // Set dialog object mouse_draw as main widget
  FWidget::setMainWidget(&board);

  // Show and start the application
  board.show();
  return app.exec();
}
