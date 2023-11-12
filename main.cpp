#include <iostream>
#include <nlohmann/json.hpp>

#include "ui.h"
#include "utils.h"
#include "mainDialog.h"
#include "websockpp.h"

using namespace std;
using namespace finalcut;

wServer s;
wClient c;
auto serverSockHandler(void){
    s.run();
}
auto clientSockHandler(void){
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
      while(1){
        sleep(2);
        json js = json::parse(R"({"happy": true, "pi": 3.141})");
        c.send(js);
      }
  }
  else{
      wThread = thread(serverSockHandler);
      while(1){
        sleep(2);
        json js = s.recv();
        cout << js.dump(2) << endl;
      }
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
