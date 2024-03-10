#include "button.h"

Button::Button (QWidget *parent):QPushButton(parent),time(new QTimer()) {}
void Button::mouseDoubleClickEvent(QMouseEvent *event) {
    emit doubleClick();
}
void Button::press(QLabel *label) {
    if(changeLock) {
        label->setText("请先出题/开始！");
        return;
    }
    time->start(250);
}
