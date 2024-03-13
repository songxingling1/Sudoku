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
#include <QFile>
#include <QTextStream>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
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
    connect(ui->decrypt,&QPushButton::clicked,this,&MainWindow::getAnswer);
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
        button->setStyleSheet("Button {"
                               "    border-style:solid;"
                               "    border-color:black;"
                               "    border-width:3;"
                               "    color:black;"
                               "    font-family:\"STSong\";"
                               "    font-size:30px;"
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
        button->setStyleSheet("Button {"
                               "    border-style:solid;"
                               "    border-color:black;"
                               "    border-width:3;"
                               "    color:black;"
                               "    font-family:\"STSong\";"
                               "    font-size:30px;"
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
        return;
    }
    ui->text->setText("做题中...");
    changeLock = 0;
    step = 3;
    time->start(10);
}
void MainWindow::ChangeTime() {
    t += 0.01;
    if(t >= 60) {
        min++;
        t = 0;
    }
    char str[20];
    sprintf(str,"%02d:%.2f",min,t);
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
    if(step == 1) {
        ui->text->setText("正在出题！");
        return;
    }
    if(step >= 2) {
        ui->text->setText("请先清盘！");
        return;
    }
    if(questionType == 0) {
        ui->text->setText("请选择出题方式！");
        return;
    }
    changeLock = 0;
    questionLock = 1;
    step = 1;
    if(questionType == 1) {
        ui->text->setText("正在出题...");
    } else {
        QFile *file = new QFile(":/json/questions.json");
        if (!file->open(QFile::ReadOnly | QFile::Text)) {
            qDebug() << "can't open error!";
            return;
        }
        QTextStream *stream = new QTextStream(file);
        stream->setEncoding(QStringConverter::System);
        QString str = stream->readAll();
        file->close();
        QJsonParseError *jsonError = new QJsonParseError();
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(),jsonError);
        if (jsonError->error != QJsonParseError::NoError && !doc.isNull()) {
            qDebug() << "Json格式错误！" << jsonError->error;
            return;
        }
        QJsonArray rootArray = doc.array();
        int id = rand() % 24;
        QJsonArray board = rootArray.at(id).toObject().value("board").toArray();
        int ind = 1;
        for(int i = 1;i <= 9;i++) {
            QJsonArray row = board.at(i - 1).toArray();
            for(int j = 1;j <= 9;j++) {
                int thisNum = row.at(j - 1).toInt();
                if(thisNum == -1) {
                    ind++;
                    continue;
                }
                getNum(thisNum,this->findChild<Button*>(QString::fromStdString("pushButton_" + to_string(thisNum))));
                Change(i,j,this->findChild<Button*>(QString::fromStdString("pushButton" + to_string(ind))));
                ind++;
            }
        }
        changeLock = 1;
        questionLock = 0;
        step = 2;
        ui->text->setText("机器出题完成！");
    }
}
void MainWindow::Clear() {
    Button *tmp;
    string ttt,tt;
    int ind = 1;
    for(int i = 1;i <= 9;i++) {
        for(int j = 1;j <= 9;j++) {
            b.erase(i,j);
            b.p[i][j] = 0;
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
    t = -0.01;
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
    step = 0;
}
void MainWindow::getAnswer() {
    if(step == 0) {
        ui->text->setText("请先出题！");
        return;
    }
    if(step == 1) {
        ui->text->setText("正在出题！");
        return;
    }
    if(step == 3) {
        time->stop();
    }
    if(step == 4) {
        ui->text->setText("请先清盘！");
        return;
    }
    b.ChangeStatus();
    bool isOk = b.getAnswer();
    if(!isOk) {
        ui->text->setText("抱歉，我做不出来！");
        return;
    }
    Button *tmp;
    string ttt;
    int ind = 1;
    for(int i = 1;i <= 9;i++) {
        for(int j = 1;j <= 9;j++) {
            ttt = "pushButton" + to_string(ind);
            tmp = this->findChild<Button*>(QString::fromStdString(ttt));
            tmp->setText(QString::fromStdString(to_string(b.getNum(i,j))));
            ind++;
        }
    }
    string tt;
    for(int i = 1;i <= 9;i++) {
        ttt = "pushButton_" + to_string(i);
        tmp = this->findChild<Button*>(QString::fromStdString(ttt));
        tt = "Button {"
             "  border-style:solid;"
             "  border-color:black;"
             "  border-width:3;"
             "  background-repeat:repeat-x;"
             "  background-image: url(:/img/has0.png);"
             "}";
        tmp->setStyleSheet(QString::fromStdString(tt));
        yu[i] = 0;
    }
    ui->text->setText("揭秘完成！");
    step = 4;
    questionLock = 0;
    changeLock = 1;
}
