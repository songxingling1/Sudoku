#ifndef BUTTON_H
#define BUTTON_H

#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QTimer>
#include "var.h"

//自定义的按钮
class Button : public QPushButton {
    Q_OBJECT
public:
    Button(QWidget* parent = nullptr);          //构造函数
    QTimer* time;
    void press(QLabel* label);          //双击预处理

protected:
    void mouseDoubleClickEvent(QMouseEvent* event);          //双击事件
signals:
    void doubleClick();          //双击信号
};

#endif          // BUTTON_H
