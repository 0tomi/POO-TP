#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "PantallaMenu/pantallamenu.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();


    return a.exec();
}
