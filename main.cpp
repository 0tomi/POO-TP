#include "mainwindow.h"
#include "./Documentos/listaacompaniantes.h"
#include "./Generadores/generadorlistaacompaniantes.h"
#include "./Documentos/listaacompaniantesui.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
