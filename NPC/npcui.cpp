#include "npcui.h"
#include "ui_npcui.h"

NPCUI::NPCUI(QWidget *parent)
    : QWidget(parent)
{   
    // Preparamos animaciones de entrada del NPC
    animacionEntrada = new QPropertyAnimation(this, "pos");
    animacionSalida = new QPropertyAnimation(this, "pos");
    connect(animacionSalida, &QPropertyAnimation::finished, this, &NPCUI::TerminoAnimacion);
    connect(animacionEntrada, &QPropertyAnimation::finished, this, &NPCUI::animacionEntrarTerminada);
    emitirDialogo.setSingleShot(true);
}

void NPCUI::Entrar(int X, int Y)
{
    PrepararAnimacionEntrada(X,Y);
    animacionEntrada->start();
    this->show();
    emit Entrando();
    if (NPCrepresentado->getDialogo() != "null"){
        connect(&emitirDialogo, &QTimer::timeout, this, &NPCUI::Hablar);
        emitirDialogo.start(1500);
    }
}

void NPCUI::Sacar(int X, int Y)
{
    PrepararAnimacionSalida(X,Y);
    animacionSalida->start();
    disconnect(&emitirDialogo, &QTimer::timeout, this, &NPCUI::Hablar);
    emit Saliendo();
}

void NPCUI::PrepararAnimacionEntrada(int X, int Y)
{
    animacionEntrada->setDuration(1000);
    animacionEntrada->setStartValue(QPoint(-(width()) -50,Y+50));
    animacionEntrada->setEndValue(QPoint(X,Y));
    animacionEntrada->setEasingCurve(QEasingCurve::OutExpo);
}

void NPCUI::PrepararAnimacionSalida(int X, int Y)
{
    animacionSalida->setDuration(1500);
    animacionSalida->setStartValue(pos());
    animacionSalida->setEndValue(QPoint(X,Y)); // SUMAR LA RESOLUCION DEL WIDGET + EL NPC
    animacionEntrada->setEasingCurve(QEasingCurve::InQuad);
}

void NPCUI::TerminoAnimacion()
{
    this->hide();
    emit this->animacionSalirTerminada();
}

void NPCUI::Hablar()
{
    // work in progress
    QString dialogo = NPCrepresentado->getDialogo();
    emit QuiereHablar(dialogo);
}

NPCUI::~NPCUI()
{
    delete animacionEntrada;
    delete animacionSalida;
}
