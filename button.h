#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <QTimer>
#include <QLabel>
#include "var.h"

class Button : public QPushButton {
    Q_OBJECT
public:
    Button (QWidget *parent = nullptr);
    QTimer *time;
    void press(QLabel *label);
protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
signals:
    void doubleClick();
};

#endif          // BUTTON_H
