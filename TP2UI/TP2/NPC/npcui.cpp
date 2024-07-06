#include "npcui.h"
#include "ui_npcui.h"

NPCUI::NPCUI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NPCUI)
{
    ui->setupUi(this);
    setFixedSize(300,300);

    // Preparamos animaciones de entrada del NPC
    animacionEntrada = new QPropertyAnimation(this, "pos");
    animacionSalida = new QPropertyAnimation(this, "pos");
    connect(animacionSalida, &QPropertyAnimation::finished, this, &NPCUI::TerminoAnimacion);
}

void NPCUI::Entrar(int X, int Y)
{
    PrepararAnimacionEntrada(X,Y);
    this->show();
    animacionEntrada->start();
}

void NPCUI::Sacar(int Y)
{
    PrepararAnimacionSalida(Y);
    animacionSalida->start();
}

void NPCUI::PrepararAnimacionEntrada(int X, int Y)
{
    animacionEntrada->setDuration(1000);
    animacionEntrada->setStartValue(QPoint(-500,Y));
    animacionEntrada->setEndValue(QPoint(X,Y));
}

void NPCUI::PrepararAnimacionSalida(int Y)
{
    animacionSalida->setDuration(1000);
    animacionSalida->setStartValue(pos());
    animacionSalida->setEndValue(QPoint(1000,Y));
}

void NPCUI::TerminoAnimacion()
{
    this->hide();
    emit this->animacionSalirTerminada();
}

NPCUI::~NPCUI()
{
    delete ui;
}
