#include "generarui.h"
#include "ui_generarui.h"

GenerarUI::GenerarUI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GenerarUI)
{
    ui->setupUi(this);

    GenerarEstancia generadorObtReglas;
    AtributosComunes generadorAtrCom;

    Juego* claseJuego = generadorObtReglas.getClaseJuego();
    if (!claseJuego) {
        return;
    }
    reglas* reglasObt = claseJuego->getReglas();
    if (!reglasObt) {
        return;
    }

    // bool valido = generadorObtReglas.getValidacion();
    // // get de info tipo visitas:
    int topeTipoVisitas = generadorObtReglas.getTopeTipoVisitas();
    string* tiposVisitas = generadorAtrCom.getVisitas(topeTipoVisitas);
    // get de info tipo visitas validas:
    int topeVisitasValidas = generadorObtReglas.getTopeTipoVisitasVals();
    string* tiposVisitasValidas = reglasObt->getTipoVisitaPermitida(topeVisitasValidas);
    // // get duracion maxima:
    int duracMaxima = reglasObt->getDuracionEstanciaPermitida();

    GenerarEstancia generadorEst(tiposVisitas, topeTipoVisitas, tiposVisitasValidas, topeVisitasValidas, duracMaxima);

    bool valido = false;
    Estancia* estancia = generadorEst.getEstancia(valido);
    if (estancia == nullptr) {
        qDebug() << "Error: estancia NULL";
        return;
    }

    string tipoVisita = estancia->getTipoEstancia();
    int duracVisita = estancia->getDuracEstancia();

    // vinculo los valores obtenidos a los label de .ui:
    // texto tipo visita:
    ui->tipoVisita->setText(QString::fromStdString(tipoVisita));
    // texto durac visita:
    ui->duracionVisita->setText(QString("%1 Meses").arg(duracVisita));
}

GenerarUI::~GenerarUI()
{
    delete ui;
}
