#include "button.h"

Button::Button (QWidget *parent):QPushButton(parent),time(new QTimer()) {}
void Button::mouseDoubleClickEvent(QMouseEvent *event) {
    emit doubleClick();
}
void Button::press() {
    time->start(250);
}
