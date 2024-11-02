#include "npcfondo.h"
#include "ui_npcfondo.h"

NPCFondo::NPCFondo(QRandomGenerator *  generador, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NPCFondo), rand(generador), estadoStandBy(false)
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
        this->primero = false;
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
    //connect(animacionAdelantar, &QAbstractAnimation::finished, this, [this](){
        //if (standBy->state() == QAbstractAnimation::Stopped)
            //standBy->stop();
    //});

    standBy = new QPropertyAnimation(ui->label, "pos");
    standBy->setEasingCurve(QEasingCurve::OutQuad);
    connect(standBy, &QAbstractAnimation::finished, this, &NPCFondo::PrepararAnimacionStandBy);

    this->move(QPoint(0, padre->height() - this->height()));
    this->show();
    this->primero = false;

    this->yNormal = ui->label->y();
    PrepararAnimacionStandBy();
}

void NPCFondo::moverAdelante()
{
    if (this->isHidden())
        return;

    if (primero) {
        this->salir();
        return;
       }

    int y = padre->height() - this->height();

    this->PrepararAnimacionAdelantar(this->x() + 130, y);
    animacionAdelantar->start();
    this->raise();
}

void NPCFondo::moverAdelanteSinSalir()
{
    if (this->isHidden())
        return;

    int y = padre->height() - this->height();

    this->PrepararAnimacionAdelantar(this->x() + 50, y);
    animacionAdelantar->start();
    this->raise();
}

void NPCFondo::moverAdelante(int x, int y)
{
    if (this->isHidden())
        return;

    if (primero) {
        this->salir();
        return;
    }

    this->PrepararAnimacionAdelantar(x, y);
    animacionAdelantar->start();
    this->raise();

   // PrepararAnimacionStandBy();
}

void NPCFondo::volverEntrar()
{
    int y = padre->height() - this->height();
    animacionEntrar->setStartValue(QPoint(-this->width(), y));
    animacionEntrar->setEndValue(QPoint(this->width() / 2 ,y));

    animacionEntrar->start();
    this->show();
}

void NPCFondo::salir()
{
    int y = padre->height() - this->height();
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

void NPCFondo::setPrimero(bool estado)
{
    primero = estado;
}

bool NPCFondo::isPrimero() const
{
    return this->primero;
}

NPCFondo::~NPCFondo()
{
    delete ui;
    delete animacionAdelantar;
    delete animacionEntrar;
    delete animacionSalir;
    delete standBy;
}

// checkeamos si un NPC se superpone con otro, dado el caso lo movemos.
void NPCFondo::updateLocation(QPoint point)
{
    int other_x = point.x();

    if (other_x > this->x() + 100 || other_x < this->x() - 100)
        return;

    this->moverAdelanteSinSalir();
}

void NPCFondo::PrepararAnimacionStandBy()
{
    standBy->setDuration(rand->bounded(300,700));

    int posY = yNormal;
    int x = ui->label->x();
    QPoint puntoBase(x, posY);

    if (estadoStandBy){
        standBy->setStartValue(ui->label->pos());
        standBy->setEndValue(puntoBase);
        estadoStandBy = false;
    } else {
        int sorteo = rand->bounded(10);
        if (sorteo < 3) {
            standBy->setStartValue(ui->label->pos());
            standBy->setEndValue(QPoint(x, yNormal + rand->bounded(10,20)));
        } else {
            standBy->setStartValue(puntoBase);
            standBy->setEndValue(puntoBase);
        }
        estadoStandBy = true;
    }

    standBy->start();
}

void NPCFondo::PrepararAnimacionAdelantar(int x, int y)
{
    animacionAdelantar->setStartValue(this->pos());
    animacionAdelantar->setEndValue(QPoint(x,y));
}
