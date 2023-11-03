#include <iostream>
#include "ui.h"
#include "utils.h"
#include "mainDialog.h"
#include "websockpp.h"
// #include "json/json.h"

using namespace std;
using namespace finalcut;

auto serverSockHandler(void){
      wServer s;
      s.run();
}
auto clientSockHandler(void){
    wClient c;
    c.run();
}
auto main (int argc, char* argv[]) -> int
{
  // freopen("/workspaces/chinese-chess/log.txt","w",stdout);
  // cout<<"Start the logfile" << endl;
  string str = "Alo!";
  LOG_F("Start the game %s", str.c_str());
  std::thread wThread;
  if (argc > 1){
      wThread = thread(clientSockHandler);
  }
  else{
      wThread = thread(serverSockHandler);
  }
  while(1);
    // std::thread thread_object (clientSockHandler);

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
