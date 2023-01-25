#include <QtWidgets/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setC();
    w.createMenus();
    w.createActions();
    w.resize(350,400);
    w.setWindowTitle("ESTGame");
    w.show();


    return a.exec();
}
