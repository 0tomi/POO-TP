#include "mainwindow.h"
#include <QApplication>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    //GameScreen g;
    //g.show();
    //g.EmpezarJuego();


    return a.exec();
}
