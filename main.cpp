#include "mainwindow.h"
#include "./Documentos/listaacompaniantes.h"
#include "./Generadores/generadorlistaacompaniantes.h"

#include <QApplication>
#include <QDebug>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GeneradorListaAcompaniantes* generador = new GeneradorListaAcompaniantes();
    ListaAcompaniantes* listaAcompInst = generador->getListaAcompaniantes();
    QString msjSinAcomp = listaAcompInst->getMensajeSinAcomp();
    QString* arr = listaAcompInst->getNombresAcomps();
    int tope = listaAcompInst->getTopeNombresAcomps();

    if (tope == 0) {
        qDebug() << "No tiene acompañante. Mensaje: ";
        qDebug() << msjSinAcomp;
    } else {
        for (int i = 0; i < tope; i++) {
            qDebug() << "acomp: " << arr[i];
        }
    }

    MainWindow w;
    w.show();

    return a.exec();
}
