#include "mainwindow.h"
#include "gamescreen.h"
#include "AtributosComunes/atributoscomunes.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // LectorArchivos test("../TP2/aceptar.txt"); Forma nueva de leer archivos
    MainWindow w;
    w.show();
    //GameScreen g;
    //g.show();

    return a.exec();
}
