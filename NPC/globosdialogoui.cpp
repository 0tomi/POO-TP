#include "globosdialogoui.h"
#include "ui_globosdialogoui.h"

GlobosDialogoUI::GlobosDialogoUI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GlobosDialogoUI)
{
    ui->setupUi(this);
    raise();
    setFixedSize(300,90);
    hide();
    TiempoVisualizacion.setSingleShot(true);
    SetearAnimacionEntrada();
    SetearAnimacionSalida();
}

void GlobosDialogoUI::setMensaje(const QString &newMensaje)
{
    mensaje = newMensaje;
    ui->Texto->setText(mensaje);
    emit MensajePreparado();
    connect(&TiempoVisualizacion, &QTimer::timeout, this, &GlobosDialogoUI::TerminarMensaje);
    MostrarMensaje();
}

void GlobosDialogoUI::MostrarMensaje()
{
    // en desarrollo
    animacionEntrada->start();
    show();
    raise();
    emit Hablando(mensaje);
    TiempoVisualizacion.start(4000);
}

void GlobosDialogoUI::ForzarSalir()
{
    if (TiempoVisualizacion.isActive()){
        TiempoVisualizacion.stop();
        TerminarMensaje();
    }
}

// ########## A futuro #############
void GlobosDialogoUI::CorrerMensaje()
{

}

GlobosDialogoUI::~GlobosDialogoUI()
{
    delete ui;
}

void GlobosDialogoUI::DarFormatoPorqueQTesHorrible(QString &formato)
{
    QString textoActual = ui->Texto->text();
    // Mantiene las etiquetas HTML y solo actualiza el contenido del texto
    QString updatedText = textoActual.section(':', 0, 0) + ": <i>" + formato + "</i>";
    ui->Texto->setText(updatedText);
}

void GlobosDialogoUI::SetearAnimacionEntrada()
{
    animacionEntrada = new QPropertyAnimation(this, "pos");
    animacionEntrada->setDuration(500);
    animacionEntrada->setStartValue(QPoint(-(width()) -50,0));
    animacionEntrada->setEndValue(QPoint(0,0));
    animacionEntrada->setEasingCurve(QEasingCurve::OutExpo);
}

void GlobosDialogoUI::SetearAnimacionSalida()
{
    opacityEffect = new QGraphicsOpacityEffect(this);
    opacityEffect->setOpacity(1.0);
    ui->Globo->setGraphicsEffect(opacityEffect);

    animacionSalida = new QPropertyAnimation(opacityEffect, "opacity");
    animacionSalida->setDuration(700);
    animacionSalida->setStartValue(1.0);
    animacionSalida->setEndValue(0.0); // Lo vuevle invisible
    connect(animacionSalida, &QPropertyAnimation::finished, this, &GlobosDialogoUI::EsconderDialogo);
}

void GlobosDialogoUI::EsconderDialogo()
{
    hide(); // Escondemos el widget
    opacityEffect->setOpacity(1.0); // Le devolvemos su opacidad
    move(-(width()),0); // Lo movemos al costado para que no moleste.
}

void GlobosDialogoUI::TerminarMensaje()
{
    raise();
    animacionSalida->start();
    // Aca estaria la animacion de que se va el globo.
    emit MensajeTerminado();
}
