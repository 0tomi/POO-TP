#include "pantallafinalnivel.h"
#include "ui_pantallafinalnivel.h"

#include <QDebug>

PantallaFinalNivel::PantallaFinalNivel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaFinalNivel)
{
    ui->setupUi(this);
}

PantallaFinalNivel::~PantallaFinalNivel()
{
    delete ui;
}

void PantallaFinalNivel::setPantallaFinalUI(Juego* juegoInfo) {
    int cantNpcsAcept = juegoInfo->getCantidadNPCsAceptados();
    int cantNpcsRech = juegoInfo->getCantidadNPCsRechazados();
    int cantMultasObt = juegoInfo->getMultas();
    int cantCredsSocsObt = juegoInfo->getSocialCreditsEarnedInLevel();

    ui->cantAcept_label->setText(QString("%1").arg(cantNpcsAcept));
    ui->cantRech_label->setText(QString("%1").arg(cantNpcsRech));
    ui->cantMultasObt_label->setText(QString("%1").arg(cantMultasObt));
    ui->credsSocsObt_label->setText(QString("%1").arg(cantCredsSocsObt));

    // conecc.signal de salirBtn:
    connect(ui->salirBtn, &QPushButton::clicked, this, &PantallaFinalNivel::on_salir_clicked);
    // connec. signal de sigNivelBtn:
    connect(ui->sigNivelBtn, &QPushButton::clicked, this, &PantallaFinalNivel::on_sigNivel_clicked);
}

// Signals
void PantallaFinalNivel::on_salir_clicked() {
    guardarPartida();
    emit salirClicked();
    qDebug() << "SALIR btn presionado y señal emitida";
}

void PantallaFinalNivel::on_sigNivel_clicked() {
    emit sigNivelClicked();
    qDebug() << "SIG NIVEL btn presionado y señal emitida";
}

// metodos extra
void PantallaFinalNivel::guardarPartida() {
    qDebug() << "partida guardada";
}
