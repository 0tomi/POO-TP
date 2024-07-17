#include "pantallaperdiste.h"
#include "ui_pantallaperdiste.h"

PantallaPerdiste::PantallaPerdiste(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaPerdiste)
{
    ui->setupUi(this);
    opacityEffect = new QGraphicsOpacityEffect(ui->stackedWidget);
    ui->stackedWidget->setGraphicsEffect(opacityEffect);
    TiempoVisualizacion.setSingleShot(true);

    inicio = new QPropertyAnimation(opacityEffect, "opacity");
    inicio->setDuration(1000);
    inicio->setStartValue(0.0);
    inicio->setEndValue(1.0); // Lo vuevle invisible

    final = new QPropertyAnimation(opacityEffect, "opacity");
    final->setDuration(1000);
    final->setStartValue(1.0);
    final->setEndValue(0.0); // Lo vuevle invisible
    connect(final, &QPropertyAnimation::finished, this, &PantallaPerdiste::FinalizoAnimacion);
    connect(&TiempoVisualizacion, &QTimer::timeout, this, &PantallaPerdiste::ArrancarFinal);
}

void PantallaPerdiste::Iniciar(bool Perdio)
{
    opacityEffect->setOpacity(0.0);
    ui->stackedWidget->setGraphicsEffect(opacityEffect);

    if (!Perdio)
        ui->stackedWidget->setCurrentWidget(ui->Pasaste);
    else
        ui->stackedWidget->setCurrentWidget(ui->Perdiste);

    show();
    inicio->start();
    TiempoVisualizacion.start(3000);
}

PantallaPerdiste::~PantallaPerdiste()
{
    delete ui;
    delete inicio;
    delete opacityEffect;
    delete final;
}

void PantallaPerdiste::ArrancarFinal()
{
    emit MidAnimacion();
    final->start();
}


void PantallaPerdiste::FinalizoAnimacion()
{
    hide();
    emit AnimacionTermino();
}
