#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MAINWINDOW w;
    w.show();
    return a.exec();
}
