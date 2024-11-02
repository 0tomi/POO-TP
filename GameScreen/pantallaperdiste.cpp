#include "pantallaperdiste.h"
#include "ui_pantallaperdiste.h"

PantallaPerdiste::PantallaPerdiste(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaPerdiste), sonidoGanar(parent), sonidoPerder(parent)
{
    ui->setupUi(this);
    padre = parent;
    MostrandoPantalla = false;

    sonidoGanar.setSource(QUrl("qrc:/Resources/Sonidos/SonidosFinalNivel/SonidoGanar.WAV"));
    sonidoPerder.setSource(QUrl("qrc:/Resources/Sonidos/SonidosFinalNivel/SonidoPerder.WAV"));
    setSoundVolume(1.0);

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

void PantallaPerdiste::setSoundVolume(float vol)
{
    sonidoGanar.setVolume(vol);
    sonidoPerder.setVolume(vol);
}

void PantallaPerdiste::Iniciar(bool Perdio)
{
    this->resize(padre->size());
    MostrandoPantalla = true;
    opacityEffect->setOpacity(0.0);
    ui->stackedWidget->setGraphicsEffect(opacityEffect);

    if (!Perdio){
        ui->stackedWidget->setCurrentWidget(ui->Pasaste);
        sonidoGanar.play();
    } else {
        ui->stackedWidget->setCurrentWidget(ui->Perdiste);
        sonidoPerder.play();
    }

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
    MostrandoPantalla = false;
    final->stop();
    TiempoVisualizacion.stop();
    emit AnimacionTermino();
}

bool PantallaPerdiste::getMostrandoPantalla() const
{
    return MostrandoPantalla;
}
