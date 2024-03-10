#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QAction>
#include "var.h"
#include "button.h"
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
    vector<int> yu;
    QTimer *time;
    double t = 0;
    int questionType = 0;
    int min = 0;

private slots:
    void Change(int x,int y,Button *button);
    void getNum(int n,Button *button);
    void Erase(int x,int y);
    void setQuestion(QAction *act);
    void Start();
    void ChangeTime();
    void Finish();
    void Question();
    void Clear();
};
#endif          // MAINWINDOW_H
