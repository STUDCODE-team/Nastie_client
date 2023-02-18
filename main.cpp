#include "mainwindow.h"

#include <QApplication>
#include <autorunmanager.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AutoRunManager::addAppAsLoginItem();

    MainWindow w;
    w.show();

    return a.exec();
}
