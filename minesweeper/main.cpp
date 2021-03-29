#include "mainwindow.h"
#include "constants.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("windows");
    MainWindow w;
    w.show();
    return a.exec();
}