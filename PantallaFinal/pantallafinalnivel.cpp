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
    int cantCredsSocsObtDia = juegoInfo->getSocialCreditsEarnedInLevel();
    int cantCredsSocsTot = juegoInfo->getTotalSocialCredits();

    ui->cantPersAcept_label->setText(QString("%1").arg(cantNpcsAcept));
    ui->cantPersRech_label->setText(QString("%1").arg(cantNpcsRech));
    ui->cantMultasObt_label->setText(QString("%1").arg(cantMultasObt));
    ui->credsSocsObtDia_label->setText(QString("%1").arg(cantCredsSocsObtDia));
    ui->credsSocsTot_label->setText(QString("%1").arg(cantCredsSocsTot));

    // conecc.signal de salirBtn:
    connect(ui->salirBtn, &QPushButton::clicked, this, &PantallaFinalNivel::onSalirClicked);
    // connec. signal de sigNivelBtn:
    connect(ui->sigNivelBtn, &QPushButton::clicked, this, &PantallaFinalNivel::onSigNivelClicked);
}

// Signals
void PantallaFinalNivel::onSalirClicked() {
    guardarPartida();
    emit salirClicked();
    qDebug() << "SALIR btn presionado y señal emitida";
}

void PantallaFinalNivel::onSigNivelClicked() {
    emit sigNivelClicked();
    qDebug() << "SIG NIVEL btn presionado y señal emitida";
}

// metodos extra
void PantallaFinalNivel::guardarPartida() {
    qDebug() << "partida guardada";
}
