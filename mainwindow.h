#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "sudoku.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow (QWidget* parent = nullptr);
    ~MainWindow ();
    int num = -1;

private:
    Ui::MainWindow* ui;
    Sudoku b;

private slots:
    void Change(int x,int y,QPushButton *b);
};
#endif          // MAINWINDOW_H
