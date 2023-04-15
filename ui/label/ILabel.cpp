#include "ui/label/ILabel.h"

Point* ILabel::getPosition() {
    return pos;
}

bool ILabel::isTargeted() {
    return target;
}