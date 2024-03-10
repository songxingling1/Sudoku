#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QList>
#include <QString>
#include <QPixmap>
#include <QCursor>
#include <QDebug>
#include <QMenu>
#include <string>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <QList>
using namespace std;

MainWindow::MainWindow (QWidget* parent)
    : QMainWindow (parent), ui (new Ui::MainWindow), yu(10,9), time(new QTimer()) {
    ui->setupUi (this);
    Button *tmp;
    string t;
    int ind = 1;
    for(int i = 1;i <= 9;i++) {
        for(int j = 1;j <= 9;j++) {
            t = "pushButton" + to_string(ind);
            tmp = this->findChild<Button*>(QString::fromStdString(t));
            tmp->setStyleSheet("QPushButton {"
                               "    border-style:solid;"
                               "    border-color:black;"
                               "    border-width:3;"
                               "    color:black;"
                               "    font-family:\"STSong\";"
                               "    font-size:30px;"
                               "    font-weight:bold;"
                               "}");
            connect(tmp,&Button::pressed,tmp,[=]()->void{tmp->press(ui->text);});
            connect(tmp->time,&QTimer::timeout,this,[=]()->void{Change(i,j,tmp);});
            connect(tmp,&Button::doubleClick,this,[=]()->void{Erase(i,j);});
            ind++;
        }
    }
    for(int i = 1;i <= 9;i++) {
        t = "pushButton_" + to_string(i);
        tmp = this->findChild<Button*>(QString::fromStdString(t));
        connect(tmp,&Button::clicked,this,[=]()->void{getNum(i,tmp);});
    }
    QMenu *menu = new QMenu();
    menu->addAction(ui->actArtificial);
    menu->addAction(ui->actRobot);
    menu->setStyleSheet("QMenu::item {"
                        "   border-style:solid;"
                        "   border-color:black;"
                        "   border-width:1;"
                        "   color:black;"
                        "   background-color: rgb(255, 255, 255);"
                        "   padding: 4px 4px 4px 4px"
                        "}");
    ui->questionbar->setMenu(menu);
    connect(ui->questionbar,&QToolButton::triggered,this,&MainWindow::setQuestion);
    connect(ui->start,&QPushButton::clicked,this,&MainWindow::Start);
    connect(this->time,&QTimer::timeout,this,&MainWindow::ChangeTime);
    connect(ui->finish,&QPushButton::clicked,this,&MainWindow::Finish);
    connect(ui->question,&QPushButton::clicked,this,&MainWindow::Question);
    connect(ui->clear,&QPushButton::clicked,this,&MainWindow::Clear);
}

MainWindow::~MainWindow () {
    delete ui;
}

void MainWindow::Change(int x, int y, Button *button) {
    button->time->stop();
    if(!questionLock && b.p[x][y]) {
        ui->text->setText("现在不可以更改题目！");
        return;
    }
    string text = button->text().toStdString();
    if(num == -1 && text == "") return;
    if(num == -1 && text != "") {
        num = stoi(text);
        QPixmap pic;
        pic.load(QString::fromStdString(":/img/pic" + text));
        QCursor cursor(pic);
        setCursor(cursor);
        button->setText("");
        b.erase(x,y);
        b.p[x][y] = 0;
        button->setStyleSheet("QPushButton {"
                               "    border-style:solid;"
                               "    border-color:black;"
                               "    border-width:3;"
                               "    color:black;"
                               "    font-family:\"STSong\";"
                               "    font-size:23px;"
                               "    font-weight:bold;"
                               "}");
        return;
    }
    if(num != -1 && text != "") {
        b.change(x,y,num);
        button->setText(QString::fromStdString(to_string(num)));
        num = stoi(text);
        QPixmap pic;
        pic.load(QString::fromStdString(":/img/pic" + text));
        QCursor cursor(pic);
        setCursor(cursor);
        return;
    }
    b.change(x,y,num);
    button->setText(QString::fromStdString(to_string(num)));
    setCursor(Qt::ArrowCursor);
    num = -1;
    b.p[x][y] = questionLock;
    if(questionLock) {
        button->setStyleSheet("QPushButton {"
                               "    border-style:solid;"
                               "    border-color:black;"
                               "    border-width:3;"
                               "    color:black;"
                               "    font-family:\"STSong\";"
                               "    font-size:23px;"
                               "    font-weight:bold;"
                               "    background-color: rgba(174, 229, 161, 190);"
                               "}");
    }
}
void MainWindow::getNum(int n,Button *button) {
    if(changeLock) {
        ui->text->setText("请先出题/开始！");
        return;
    }
    if(num == -1 && yu[n] == 0) {
        return;
    }
    if(num == -1) {
        num = n;
        QPixmap pic;
        pic.load(QString::fromStdString(":/img/pic" + to_string(n)));
        QCursor cursor(pic);
        setCursor(cursor);
        yu[n]--;
        string tmp = "Button {"
                     "  border-style:solid;"
                     "  border-color:black;"
                     "  border-width:3;"
                     "  background-repeat:repeat-x;"
                     "  background-image: url(:/img/has" + to_string(yu[n]) + ".png);"
                     "}";
        button->setStyleSheet(QString::fromStdString(tmp));
        return;
    }
    if(num != -1 && n == num) {
        num = -1;
        setCursor(Qt::ArrowCursor);
        yu[n]++;
        string tmp = "Button {"
                     "  border-style:solid;"
                     "  border-color:black;"
                     "  border-width:3;"
                     "  background-repeat:repeat-x;"
                     "  background-image: url(:/img/has" + to_string(yu[n]) + ".png);"
                     "}";
        button->setStyleSheet(QString::fromStdString(tmp));
    }
}
void MainWindow::Erase(int x,int y) {
    if(changeLock) {
        ui->text->setText("请先出题/开始！");
        return;
    }
    if(!questionLock && b.p[x][y]) {
        ui->text->setText("现在不可以更改题目！");
        return;
    }
    int temp = b.getNum(x,y);
    if(temp == -1) return;
    Button *tmp = this->findChild<Button*>(QString::fromStdString("pushButton_" + to_string(temp)));
    tmp->time->stop();
    Change(x,y,this->findChild<Button*>(QString::fromStdString("pushButton" + to_string((x - 1) * 9 + y))));
    getNum(temp,tmp);
    b.erase(x,y);
}
void MainWindow::setQuestion(QAction *act) {
    if(questionLock == 1) {
        ui->text->setText("正在出题！");
        return;
    }
    if(questionLock == 2) {
        ui->text->setText("出题已经完成！");
        return;
    }
    if(questionLock == 3) {
        ui->text->setText("正在做题！");
        return;
    }
    if(questionLock == 4) {
        ui->text->setText("请先清盘！");
        return;
    }
    if(act->objectName() == "actArtificial") {
        questionType = 1;
        ui->question->setText("人工出题");
    } else {
        questionType = 2;
        ui->question->setText("机器出题");
    }
    ui->text->setText("出题方式选择完成。");
}
void MainWindow::Start() {
    if(step == 0) {
        ui->text->setText("请先出题！");
        return;
    }
    if(step == 1) {
        ui->text->setText("正在出题！");
        return;
    }
    if(step == 3) {
        ui->text->setText("正在做题！");
        return;
    }
    if(step == 4) {
        ui->text->setText("请先清盘！");
    }
    ui->text->setText("做题中...");
    changeLock = 0;
    step = 3;
    time->start(1);
}
void MainWindow::ChangeTime() {
    t += 0.001;
    if(t >= 60) {
        min++;
        t = 0;
    }
    char str[20];
    sprintf(str,"%03d:%.3f",min,t);
    ui->time->setText(QString::fromStdString(string(str)));
}
void MainWindow::Finish() {
    if(step == 1) {
        ui->text->setText("出题完成。");
        questionLock = 0;
        changeLock = 1;
        step = 2;
        return;
    }
    if(step == 3) {
        CheckStatus check = b.check();
        if(check == CheckStatus::SUCCESE) {
            ui->text->setText("通过！");
            changeLock = 1;
            time->stop();
            step = 4;
            return;
        } else if(check == CheckStatus::INCOMPLETE) {
            ui->text->setText("没有做完！");
            return;
        } else {
            ui->text->setText("答案错误！");
            return;
        }
    }
    ui->text->setText("没有正在进行的任务！");
}
void MainWindow::Question() {
    if(questionType == 0) {
        ui->text->setText("请选择出题方式！");
        return;
    }
    if(questionType == 1) {
        changeLock = 0;
        questionLock = 1;
        step = 1;
        ui->text->setText("正在出题...");
    } else {
        // TODO : 自动放数
    }
}
void MainWindow::Clear() {
    Button *tmp;
    string ttt,tt;
    int ind = 1;
    for(int i = 1;i <= 9;i++) {
        for(int j = 1;j <= 9;j++) {
            b.erase(i,j);
            ttt = "pushButton" + to_string(ind);
            tmp = this->findChild<Button*>(QString::fromStdString(ttt));
            tmp->setStyleSheet("QPushButton {"
                                "    border-style:solid;"
                                "    border-color:black;"
                                "    border-width:3;"
                                "    color:black;"
                                "    font-family:\"STSong\";"
                                "    font-size:30px;"
                                "    font-weight:bold;"
                                "}");
            tmp->setText("");
            ind++;
        }
    }
    for(int i = 1;i <= 9;i++) {
        ttt = "pushButton_" + to_string(i);
        tmp = this->findChild<Button*>(QString::fromStdString(ttt));
        tt = "Button {"
                     "  border-style:solid;"
                     "  border-color:black;"
                     "  border-width:3;"
                     "  background-repeat:repeat-x;"
                     "  background-image: url(:/img/has9.png);"
                     "}";
        tmp->setStyleSheet(QString::fromStdString(tt));
        yu[i] = 9;
    }
    t = -0.001;
    min = 0;
    questionType = 0;
    questionLock = 0;
    changeLock = 1;
    if(time->isActive()) {
        time->stop();
    }
    ui->question->setText("出题");
    ui->text->setText("数独游戏");
    ChangeTime();
}
