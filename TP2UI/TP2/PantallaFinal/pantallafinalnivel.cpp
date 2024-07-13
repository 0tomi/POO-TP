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
    ui->credsSocObts->setText(QString("%1").arg(juegoInfo->getSocialCreditsEarnedInLevel()));
    ui->multasObt->setText(QString("%1").arg(juegoInfo->getMultas()));

    // conecc.signal de salirBtn:
    connect(ui->salirBtn, &QPushButton::clicked, this, &PantallaFinalNivel::on_salir_clicked);
    // connec. signal de sigNivelBtn:
    connect(ui->sigNivelBtn, &QPushButton::clicked, this, &PantallaFinalNivel::on_sigNivel_clicked);
}

void PantallaFinalNivel::on_salir_clicked() {
    emit salirClicked();
    qDebug() << "SALIR btn presionado y señal emitia";
}

void PantallaFinalNivel::on_sigNivel_clicked() {
    emit sigNivelClicked();
    qDebug() << "SIG NIVEL btn presionado y señal emitida";
}
