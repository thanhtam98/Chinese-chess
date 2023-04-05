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

  board.setGeometry(FPoint{1, 1}, FSize{60, 60}, false);

  // Set dialog object mouse_draw as main widget
  FWidget::setMainWidget(&board);

  // Show and start the application
  board.show();
  return app.exec();
}

// auto main (int argc, char* argv[]) -> int 
// {; 
//     printf("%c\n", 14); 
//     printf("┌──┬──┬\n") ; 
//     printf("├─┼─┼\n") ; 
//     printf("┌", 0x6C) ; 
//     printf("%c ", 0x6D) ;// # └
//     printf("%c ", 0x6E) ;// # ┼ 
//     printf("%c ", 0x71) ;// # ─
//     printf("%c ", 0x74) ;// # ├
//     printf("%c ", 0x75) ;// # ┤
//     printf("%c ", 0x76) ;// # ┴
//     printf("%c ", 0x77) ;// # ┬
//     printf("%c\n", 0x78);//  # │

//   FApplication app(argc, argv);
//   auto lamda = [] (FButton& button, FDialog& dgl)  // Lambda function
//     {
//       button.setColor(FColor::LightRed, FColor::Black);
//       dgl.redraw();
//     };

//   // The object dialog is managed by app
//   FDialog* dialog = new FDialog(&app);
//   dialog->setText ("Window Title");
//   dialog->setGeometry (FPoint{25, 5}, FSize{40, 10});

//   // The object input is managed by dialog
//   FLineEdit* input = new FLineEdit("predefined text", dialog);
//   input->setGeometry(FPoint{8, 2}, FSize{29, 1});
//   input->setLabelText (L"&Input");


//   // The object label is managed by dialog
//   FButton button{"車", dialog};
//   button.setGeometry (FPoint{9, 5}, FSize{4, 1});
//   button.unsetShadow(); 
//   button.addCallback("clicked", lamda, std::ref(button), std::ref(*dialog));

//   FButton button2{"車", dialog};
//   button2.setGeometry (FPoint{13, 5}, FSize{4, 1});
//   button2.unsetShadow(); 
//   button2.addCallback("clicked", lamda, std::ref(button), std::ref(*dialog));

//   FLabel* label1 = new FLabel ( "┌───┬──\n│ ╲ │ \n├───┼─\n"
//                              , dialog );
//   label1->setGeometry (FPoint{3, 5}, FSize{6, 3});

//   FLabel* label2 = new FLabel ( "╱ │   │\n──┼───┼\n"
//                              , dialog );
//   label2->setGeometry (FPoint{9, 6}, FSize{7, 2});

//   FWidget::setMainWidget(dialog);
//   dialog->show();
//   return app.exec();

// }



// class dialogWidget : public FDialog
// {
//   public:
//     explicit dialogWidget (FWidget* parent = nullptr)
//       : FDialog{parent}
//     {
//       scrollview.setGeometry(FPoint{1, 1}, FSize{22, 11});
//       scrollview.setScrollSize(FSize{60, 27});
//       // Attention: getColorTheme() requires an initialized terminal
//       const auto& wc = getColorTheme();
//       setColor (wc->label_inactive_fg, wc->dialog_bg);
//       scrollview.clearArea();
//       FColorPair red (FColor::LightRed, wc->dialog_bg);
//       FColorPair black (FColor::Black, wc->dialog_bg);
//       FColorPair cyan (FColor::Cyan, wc->dialog_bg);

//       static std::vector<direction> d
//       {
//         {"NW", FPoint{3,  13}, FPoint{1,  1},  black},
//         {"N",  FPoint{10, 13}, FPoint{21, 1},  red},
//         {"NE", FPoint{17, 13}, FPoint{41, 1},  black},
//         {"W",  FPoint{3,  15}, FPoint{1,  10}, black},
//         {"*",  FPoint{10, 15}, FPoint{21, 10}, black},
//         {"E",  FPoint{17, 15}, FPoint{41, 10}, black},
//         {"SW", FPoint{3,  17}, FPoint{1,  19}, black},
//         {"S",  FPoint{10, 17}, FPoint{21, 19}, cyan},
//         {"SE", FPoint{17, 17}, FPoint{41, 19}, black}
//       };

//       for (auto&& b : d)
//       {
//         scrollview.print() << std::get<2>(b) + FPoint{10, 5}
//                            << std::get<3>(b) << std::get<0>(b);
//         auto edit = new FLineEdit("direction " + std::get<0>(b), &scrollview);
//         edit->setGeometry(std::get<2>(b) + FPoint{1, 1}, FSize{17, 1});
//         auto btn = new FButton(std::move(std::get<0>(b)), this);
//         btn->setGeometry(std::get<1>(b), FSize{4, 1});
//         btn->unsetShadow();
//         btn->addCallback
//         (
//           "clicked",
//           this, &dialogWidget::cb_button, std::get<2>(b)
//         );
//       }
//     }

//   private:
//     typedef std::tuple<FString, FPoint, FPoint, FColorPair> direction;

//     void initLayout()
//     {
//       setText ("Dialog");
//       setGeometry (FPoint{28, 2}, FSize{24, 21});
//       FDialog::initLayout();
//     }

//     void cb_button (const FPoint& p)
//     {
//       scrollview.scrollTo(p);
//     }

//     FScrollView scrollview{this};
// };

// auto main (int argc, char* argv[]) -> int
// {
//   FApplication app(argc, argv);
//   app.initTerminal();  // Terminal initialization
//   dialogWidget dialog(&app);
//   FWidget::setMainWidget(&dialog);
//   dialog.show();
//   return app.exec();
// }