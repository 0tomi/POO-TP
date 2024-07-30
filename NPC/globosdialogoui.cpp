#include "globosdialogoui.h"
#include "ui_globosdialogoui.h"

GlobosDialogoUI::GlobosDialogoUI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GlobosDialogoUI)
{
    ui->setupUi(this);
    tamanioNormalGloboX = 300; tamanioNormalGloboY = 90;
    tamanioAumentadoGloboX = tamanioNormalGloboX + 15;
    tamanioAumentadoGloboY = tamanioNormalGloboY + 40;

    setFixedSize(tamanioNormalGloboX,tamanioNormalGloboY);
    hide();
    TiempoVisualizacion.setSingleShot(true);
    SetearAnimacionEntrada();
    SetearAnimacionSalida();
    Mostrandose = false;
}

void GlobosDialogoUI::setMensaje(const QString &newMensaje, const int X, const int Y)
{
    mensaje = newMensaje;
    ui->Texto->setText(mensaje);

    if (mensaje.length() > 45)
        setFixedSize(tamanioAumentadoGloboX,tamanioAumentadoGloboY);
    else
        setFixedSize(tamanioNormalGloboX,tamanioNormalGloboY);

    emit MensajePreparado();
    connect(&TiempoVisualizacion, &QTimer::timeout, this, &GlobosDialogoUI::TerminarMensaje);
    PrepararAnimacionEntrada(X, Y);
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

void GlobosDialogoUI::PausarMensaje()
{
    if (Mostrandose){
        tiempoRestante = TiempoVisualizacion.remainingTime();
        TiempoVisualizacion.stop();
    }
}

void GlobosDialogoUI::ReanudarMensaje()
{
    if (Mostrandose)
        TiempoVisualizacion.start(tiempoRestante);
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
    delete animacionEntrada;
    delete animacionSalida;
    delete opacityEffect;
}

void GlobosDialogoUI::Centrar(int X, int Y)
{
    if (Mostrandose){
        CalcularPosicionDelGlobo(X, Y);
        move(X,Y);
        raise();
    }
}

void GlobosDialogoUI::SetearAnimacionEntrada()
{
    animacionEntrada = new QPropertyAnimation(this, "pos");
    animacionEntrada->setDuration(500);
    animacionEntrada->setEasingCurve(QEasingCurve::OutExpo);
    connect(animacionEntrada, &QPropertyAnimation::finished, this, &GlobosDialogoUI::setMostrandose);
}

void GlobosDialogoUI::PrepararAnimacionEntrada(int X, int Y)
{
    int PosOcultaY = Y;
    CalcularPosicionDelGlobo(X,Y);

    animacionEntrada->setStartValue(QPoint(X, PosOcultaY)); // Coloca el globo oculto por debajo de la pantalla
    animacionEntrada->setEndValue(QPoint(X,Y));             // Sube el globo para que se vea en el medio de la pantalla
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

void GlobosDialogoUI::CalcularPosicionDelGlobo(int &X, int &Y)
{
    X = (X - width()) / 2;    // Centro de la pantalla con respecto al eje horizontal
    Y = Y-height();          // Altura en la cual se ve el widget por encima de la pantalla.
}

void GlobosDialogoUI::setMostrandose()
{
    Mostrandose = true;
}

void GlobosDialogoUI::TerminarMensaje()
{
    raise();
    animacionSalida->start();
    Mostrandose = false;
    // Aca estaria la animacion de que se va el globo.
    emit MensajeTerminado();
}
