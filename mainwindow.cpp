#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QList>
#include <QString>
#include <QPixmap>
#include <QCursor>
#include <QDebug>
#include <string>
#include <cmath>
#include <cstring>
#include <QList>
using namespace std;

MainWindow::MainWindow (QWidget* parent)
    : QMainWindow (parent), ui (new Ui::MainWindow), yu(10,9) {
    ui->setupUi (this);
    Button *tmp;
    string t;
    int ind = 1;
    for(int i = 1;i <= 9;i++) {
        for(int j = 1;j <= 9;j++) {
            t = "pushButton" + to_string(ind);
            tmp = this->findChild<Button*>(QString::fromStdString(t));
            tmp->setStyleSheet("Button {"
                                "   color:black;"
                                "   font-family:\"STSong\";"
                                "   font-size:20pt;"
                                "}");
            tmp->setMaximumWidth(40);
            connect(tmp,&Button::pressed,tmp,&Button::press);
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
}

MainWindow::~MainWindow () {
    delete ui;
}

void MainWindow::Change(int x, int y, Button *button) {
    button->time->stop();
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
}
void MainWindow::getNum(int n,Button *button) {
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
                     "  background-image: url(:/img/has" + to_string(yu[n]) + ".png);"
                     "}";
        button->setStyleSheet(QString::fromStdString(tmp));
    }
}
void MainWindow::Erase(int x,int y) {
    int temp = b.getNum(x,y);
    if(temp == -1) return;
    Button *tmp = this->findChild<Button*>(QString::fromStdString("pushButton_" + to_string(temp)));
    tmp->time->stop();
    Change(x,y,this->findChild<Button*>(QString::fromStdString("pushButton" + to_string((x - 1) * 9 + y))));
    getNum(temp,tmp);
    b.erase(x,y);
}
