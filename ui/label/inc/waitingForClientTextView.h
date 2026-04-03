#pragma once

#include "final/final.h"

using namespace finalcut;

class WaitingForClientTextView : public FTextView {
public:
    explicit WaitingForClientTextView(FWidget* parent) : FTextView{parent} {};
private:
    void draw() override;
};