#include "globosdialogoui.h"
#include "ui_globosdialogoui.h"
#include <QTime>

GlobosDialogoUI::GlobosDialogoUI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GlobosDialogoUI), Random(QTime::currentTime().msec()), interrumpirMensaje(false)
{
    padre = parent;
    ui->setupUi(this);

    URLSonidos[0].setUrl("qrc:/Resources/Sonidos/Dialogos/DialogoSound1.WAV");
    URLSonidos[1].setUrl("qrc:/Resources/Sonidos/Dialogos/DialogoSound2.WAV");
    URLSonidos[2].setUrl("qrc:/Resources/Sonidos/Dialogos/DialogoSound3.WAV");
    URLSonidos[3].setUrl("qrc:/Resources/Sonidos/Dialogos/DialogoSound4.WAV");
    Sonido.setVolume(1.0);

    tamanioNormalGloboX = 300; tamanioNormalGloboY = 90;
    tamanioAumentadoGloboX = tamanioNormalGloboX + 15;
    tamanioAumentadoGloboY = tamanioNormalGloboY + 40;

    setFixedSize(tamanioNormalGloboX,tamanioNormalGloboY);
    hide();
    TiempoVisualizacion.setSingleShot(true);
    SetearAnimacionEntrada();
    SetearAnimacionSalida();
    Mostrandose = false;

    connect(&TiempoVisualizacion, &QTimer::timeout, this, &GlobosDialogoUI::TerminarMensaje);
}

void GlobosDialogoUI::setMensaje(const QString &newMensaje)
{
    mensaje = newMensaje;
    ui->Texto->setText(mensaje);

    if (mensaje.length() > 60)
        setFixedSize(tamanioAumentadoGloboX,tamanioAumentadoGloboY+15);
    else
        if (mensaje.length() > 45)
            setFixedSize(tamanioAumentadoGloboX,tamanioAumentadoGloboY);
        else
            setFixedSize(tamanioNormalGloboX,tamanioNormalGloboY);

    emit MensajePreparado();
    PrepararAnimacionEntrada();
    MostrarMensaje();
}

void GlobosDialogoUI::MostrarMensaje()
{
    if (interrumpirMensaje)
        return;
    animacionEntrada->start();
    show();
    raise();
    emit Hablando(mensaje);
    TiempoVisualizacion.start(6000);
    ReproducirSonido();
    Mostrandose = true;
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

void GlobosDialogoUI::InterrumpirMensaje(bool estado)
{
    this->interrumpirMensaje = estado;
}

void GlobosDialogoUI::ForzarSalir()
{
    if (Mostrandose){
        TiempoVisualizacion.stop();
        TerminarMensaje();
    }
}

void GlobosDialogoUI::Finalizar()
{
    this->ForzarSalir();
    this->InterrumpirMensaje(true);
    this->Sonido.stop();
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

void GlobosDialogoUI::Centrar()
{
    if (Mostrandose){
        int X = padre->width(); int Y = padre->height();
        CalcularPosicionDelGlobo(X,Y);
        move(X,Y);
        raise();
    }
}

void GlobosDialogoUI::setVolume(float vol)
{
    Sonido.setVolume(vol);
}

void GlobosDialogoUI::SetearAnimacionEntrada()
{
    animacionEntrada = new QPropertyAnimation(this, "pos");
    animacionEntrada->setDuration(500);
    animacionEntrada->setEasingCurve(QEasingCurve::OutExpo);
}

void GlobosDialogoUI::PrepararAnimacionEntrada()
{
    int X = padre->width(); int Y = padre->height();
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

void GlobosDialogoUI::ReproducirSonido()
{
    int sorteo = Random.bounded(4);
    Sonido.setSource(URLSonidos[sorteo]);
    Sonido.play();
}

void GlobosDialogoUI::TerminarMensaje()
{
    raise();
    animacionSalida->start();
    Mostrandose = false;
    emit MensajeTerminado();
}
