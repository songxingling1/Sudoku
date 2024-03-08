#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QList>
#include <QString>
#include <QPixmap>
#include <QCursor>
#include <string>
#include <cmath>
#include <cstring>
using namespace std;

MainWindow::MainWindow (QWidget* parent)
    : QMainWindow (parent), ui (new Ui::MainWindow) {
    ui->setupUi (this);
    QPushButton *tmp;
    string t;
    int ind = 1;
    for(int i = 1;i <= 9;i++) {
        for(int j = 1;j <= 9;j++) {
            t = "pushButton" + to_string(ind);
            tmp = this->findChild<QPushButton*>(QString(QString::fromLocal8Bit(t)));
            tmp->setStyleSheet("QPushButton {"
                                "   color:black;"
                                "   font-family:\"STSong\";"
                                "   font-size:20pt;"
                                "}");
            tmp->setMaximumWidth(40);
            connect(tmp,&QPushButton::clicked,this,[=]()->void{Change(i,j,tmp);});
            ind++;
        }
    }
}

MainWindow::~MainWindow () {
    delete ui;
}

void MainWindow::Change(int x, int y, QPushButton *button) {
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

