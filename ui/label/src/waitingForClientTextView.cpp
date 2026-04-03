#include "waitingForClientTextView.h"
#include "configurator.h"

void WaitingForClientTextView::draw() {
    setColor(FColor::Black, FColor::White);
    print() << "The server now listen on:\n";
    setColor(FColor::White, FColor::Green4);
    print() << Configurator::get(IP) + ":" + Configurator::get(PORT) + "\n";
    setColor(FColor::Black, FColor::White);
    print() << "Please wait for your opponent!";
}