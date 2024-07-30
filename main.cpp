#include "mainwindow.h"
#include "./Documentos/listaacompaniantes.h"
#include "./Generadores/generadorlistaacompaniantes.h"
#include "./Documentos/listaacompaniantesui.h"
#include "./GameScreen/pantallatutorial.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PantallaTutorial b;
    b.show();
    MainWindow w;
    w.show();

    return a.exec();
}
