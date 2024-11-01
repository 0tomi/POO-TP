#include "npcfondo.h"
#include "ui_npcfondo.h"

NPCFondo::NPCFondo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NPCFondo)
{
    ui->setupUi(this);
    padre = parent;
    // Preparamos animaciones de entrada del NPC
    animacionSalir = new QPropertyAnimation(this, "pos");
    animacionSalir->setDuration(1000);
    animacionSalir->setEasingCurve(QEasingCurve::OutQuad);
    connect(animacionSalir, &QAbstractAnimation::finished, this, [this](){
        this->hide();
        emit this->Salio();
    });

    animacionEntrar = new QPropertyAnimation(this, "pos");
    animacionEntrar->setDuration(1000);
    animacionEntrar->setEasingCurve(QEasingCurve::OutQuad);
    connect(animacionEntrar, &QAbstractAnimation::finished, this, [this](){
        emit Entro();
        emit Posicion(this->pos());
    });

    animacionAdelantar = new QPropertyAnimation(this, "pos");
    animacionAdelantar->setDuration(1000);
    animacionAdelantar->setEasingCurve(QEasingCurve::OutQuad);    // La animacion se desacelera conforme entra
    connect(animacionAdelantar, &QAbstractAnimation::finished, this, [this](){
        emit Posicion(this->pos());
    });

    this->move(QPoint(0, padre->height() / 3));
    this->show();
}

void NPCFondo::moverAdelante()
{
    this->PrepararAnimacionAdelantar(this->x() + 15, this->y());
    animacionAdelantar->start();
    this->raise();
}

void NPCFondo::moverAdelante(int x, int y)
{
    this->PrepararAnimacionAdelantar(x, y);
    animacionAdelantar->start();
    this->raise();
}

void NPCFondo::volverEntrar()
{
    int y = padre->height() / 3;
    animacionEntrar->setStartValue(QPoint(-this->width(), y));
    animacionEntrar->setEndValue(QPoint(this->width(),y));

    animacionEntrar->start();
    this->show();
}

void NPCFondo::salir()
{
    int y = padre->height() / 3;
    animacionSalir->setStartValue(this->pos());
    animacionSalir->setEndValue(QPoint(padre->width() + this->width(), y));

    animacionSalir->start();
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
}

NPCFondo::~NPCFondo()
{
    delete ui;
    delete animacionAdelantar;
}

// checkeamos si un NPC se superpone con otro, dado el caso lo movemos.
void NPCFondo::updateLocation(QPoint point)
{
    int other_x = point.x();

    if (other_x > this->x() + 10 || other_x < this->x() - 10)
        return;

    this->moverAdelante();
}

void NPCFondo::PrepararAnimacionAdelantar(int x, int y)
{
    animacionAdelantar->setStartValue(this->pos());
    animacionAdelantar->setEndValue(QPoint(x,y));
}
