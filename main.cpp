#include <QApplication>
#include <QGridLayout>
#include "mainwindow.h"

int main (int argc, char* argv[]) {
    QApplication a (argc, argv);
    MainWindow w;
    w.setWindowFlags(w.windowFlags()&~Qt::WindowMinMaxButtonsHint|Qt::WindowMinimizeButtonHint);
    w.show ();
    return a.exec ();
}
