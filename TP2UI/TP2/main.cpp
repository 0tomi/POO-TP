#include "mainwindow.h"
#include "gamescreen.h"
#include <QApplication>
#include <QDebug>
#include "Documentos/estanciaui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // LectorArchivos test("../TP2/aceptar.txt"); Forma nueva de leer archivos
    MainWindow w;
    w.show();

    //GameScreen g;
    //g.show();
    //g.EmpezarJuego();

    estanciaUI h;
    h.show();

    return a.exec();
}
