#include "mainwindow.h"
#include "gamescreen.h"
#include <QApplication>
#include <QDebug>
#include "GameScreen/tomibotones.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // LectorArchivos test("../TP2/aceptar.txt"); Forma nueva de leer archivos
    MainWindow w;
    w.show();

    QString BotonRechazarDesbloqueado = ":/Resources/MaterialPantallas/BotonDesaprobarNoApretado .png";
    QString BotonRechazarBloqueado = ":/Resources/MaterialPantallas/BotonDesaprobarApretado.png";

    TomiBotones test(BotonRechazarDesbloqueado, BotonRechazarBloqueado);
    test.show();
    //GameScreen g;
    //g.show();
    //g.EmpezarJuego();

    return a.exec();
}
