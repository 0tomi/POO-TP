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

void PantallaFinalNivel::setPantallaFinalUI(Juego* juegoInfo, bool perdio) {
    int cantNpcsAcept = juegoInfo->getCantidadNPCsAceptados();
    int cantNpcsRech = juegoInfo->getCantidadNPCsRechazados();
    int cantMultasObt = juegoInfo->getMultas();
    int maxMultas = juegoInfo->getMaxMultas();
    int cantCredsSocsObtDia = juegoInfo->getSocialCreditsEarnedInLevel();
    int cantCredsSocsTot = juegoInfo->getTotalSocialCredits();

    // manejo del stacked widget dependiendo si perdio o gano:
    if (perdio) {
        // ui->stackedTitulos->setCurrentIndex(1);
        // ui->stackedBotones->setCurrentIndex(1);
    } else {
        // ui->stackedTitulos->setCurrentIndex(0);
        // ui->stackedBotones->setCurrentIndex(0);
    }

    ui->cantPersAcept_label->setText(QString("%1").arg(cantNpcsAcept));
    ui->cantPersRech_label->setText(QString("%1").arg(cantNpcsRech));
    ui->cantMultasObt_label->setText(QString("%1").arg(cantMultasObt));
    if (cantMultasObt == maxMultas) {
        ui->cantMultasObt_label->setStyleSheet("#cantMultasObt_label { color: red; }");
    }
    ui->credsSocsObtDia_label->setText(QString("%1").arg(cantCredsSocsObtDia));
    if (cantCredsSocsObtDia < 1) {
        ui->credsSocsObtDia_label->setStyleSheet("#credsSocsObtDia_label { color: red; }");
    }
    ui->credsSocsTot_label->setText(QString("%1").arg(cantCredsSocsTot));
    if (cantCredsSocsObtDia < 1) {
        ui->credsSocsTot_label->setStyleSheet("#credsSocsTot_label { color: red; }");
    }

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
