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
}

void NPCUI::Entrar(int X, int Y)
{
    PrepararAnimacionEntrada(X,Y);
    animacionEntrada->start();
    this->show();
}

void NPCUI::Sacar(int X, int Y)
{
    PrepararAnimacionSalida(X,Y);
    animacionSalida->start();
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

NPCUI::~NPCUI()
{
    delete animacionEntrada;
    delete animacionSalida;
}
