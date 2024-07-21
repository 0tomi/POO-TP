#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "./GameScreen/libroreglas.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    LibroReglas s;
    s.show();
    //GameScreen g;
    //g.show();
    //g.EmpezarJuego();


    return a.exec();
}
