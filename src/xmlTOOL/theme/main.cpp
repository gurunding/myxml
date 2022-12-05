#include "theme.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    THEME w;
    w.show();
    return a.exec();
}
