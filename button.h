#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <QTimer>

class Button : public QPushButton {
    Q_OBJECT
public:
    Button (QWidget *parent = nullptr);
    QTimer *time;
    void press();
protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
signals:
    void doubleClick();
};

#endif          // BUTTON_H
