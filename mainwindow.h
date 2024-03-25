#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QTimer>
#include "button.h"
#include "sudoku.h"
#include "var.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
// 主窗口类
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    int num = -1;

private:
    Ui::MainWindow* ui;
    Sudoku b;          //棋盘
    vector<int> yu;          //取数板剩余数字
    QTimer* time;          //计时器
    QMenu* menu;          //出题方式菜单
    QMenu* secmenu;          //难度二级菜单
    double t = 0;          //时间秒数
    int questionType = 0;          //出题方式
    int min = 0;          //时间分钟数
    int level = 0;          //问题难度

private slots:
    void Change(int x, int y, Button* button);          //更改棋盘某一位
    void getNum(int n, Button* button);          //获取一个数
    void Erase(int x, int y);          //快捷放回
    void setQuestion(QAction* act);          //设置出题方式
    void Start();          //开始做题
    void ChangeTime();          //改变时间
    void Finish();          //结束
    void Question();          //出题
    void Clear();          //清盘
    void getAnswer();          //揭秘
    void showMainMenu();          //展示出题方式窗口
    void showSecondMenu(QAction* act);          //展示难度窗口
    void stopTimer();          //停止计时
};
#endif          // MAINWINDOW_H
