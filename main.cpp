#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "Documentos/pasaporteui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    PasaporteUI pas;
    pas.show();

    //GameScreen g;
    //g.show();
    //g.EmpezarJuego();


    return a.exec();
}
