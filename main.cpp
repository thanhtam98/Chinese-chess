#include <iostream>
#include <nlohmann/json.hpp>

#include "ui.h"
#include "utils.h"
#include "mainDialog.h"
#include "websockpp.h"
#include "transfer.h"

using namespace std;
using namespace finalcut;

wServer s;
wClient c;
void a (Point *from, Point *to){
  cout << "MOVE " << *from << *to << endl;
}
void b (Point *from){
  cout << "SEL: " << *from  << endl;
}
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
      transfer trans{&c};
      trans.setCallback(a,b);
      while(1){
        sleep(2);
        // trans.sendMsg(MOV, Point::of(3,2), Point::of(4,2));
        // trans.sendMsg(SEL, Point::of(2,2));
      }
  }
  else{
      wThread = thread(serverSockHandler);
      transfer trans{&s};
      trans.setCallback(a,b);
      while(1){
        sleep(2);
        trans.sendMsg(MOV, Point::of(3,2), Point::of(4,2));
        trans.sendMsg(SEL, Point::of(2,2));
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
