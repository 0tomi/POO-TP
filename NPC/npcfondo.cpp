#include "npcfondo.h"
#include "ui_npcfondo.h"

NPCFondo::NPCFondo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NPCFondo)
{
    ui->setupUi(this);
    padre = parent;
    // Preparamos animaciones de entrada del NPC
    animacionAdelantar = new QPropertyAnimation(this, "pos");
    animacionAdelantar->setDuration(1000);
    animacionAdelantar->setEasingCurve(QEasingCurve::OutQuad);    // La animacion se desacelera conforme entra
    this->move(QPoint(0, padre->height() / 3));
}

void NPCFondo::MoverAdelante(NPCFondo *anterior)
{
    qDebug() << "Arranco mover adelante, x: " << this->x() << " | y: " << this->y();
    int x;
    if (anterior == nullptr)
        x = this->width();
    else x = anterior->x() + this->width();

    int y = this->y();
    PrepararAnimacionAdelantar(x,y);
    animacionAdelantar->start();
    this->raise();
    qDebug() << "Termino mover adelante, x: " << this->x() << " | y: " << this->y();
}

NPCFondo::~NPCFondo()
{
    delete ui;
    delete animacionAdelantar;
}

void NPCFondo::PrepararAnimacionAdelantar(int x, int y)
{
    animacionAdelantar->setStartValue(this->pos());
    animacionAdelantar->setEndValue(QPoint(x,y));
}
