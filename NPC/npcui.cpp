#include "npcui.h"
#include "ui_npcui.h"

NPCUI::NPCUI(QWidget *parent)
    : QWidget(parent), estadoAnimacionStandby(false)
{
    padre = parent;

    // Preparamos animaciones de entrada del NPC
    animacionEntrada = new QPropertyAnimation(this, "pos");
    animacionEntrada->setDuration(1000);
    animacionEntrada->setEasingCurve(QEasingCurve::OutQuad);    // La animacion se desacelera conforme entra

    animacionStandBy = new QPropertyAnimation(this, "pos");
    animacionStandBy->setEasingCurve(QEasingCurve::InQuad);

    // Preparamos animaciones de salida del NPC
    animacionSalida = new QPropertyAnimation(this, "pos");
    animacionSalida->setDuration(1500);
    animacionSalida->setEasingCurve(QEasingCurve::InQuad);  // La animacion se acelera conforme sale

    connect(animacionSalida, &QPropertyAnimation::finished, this, &NPCUI::TerminoAnimacion);
    connect(animacionEntrada, &QPropertyAnimation::finished, [this](){
        emit animacionEntrarTerminada();
        Mostrandose = true;
        PrepararAnimacionStandBy();
        animacionStandBy->start();
    });
    connect(animacionStandBy, &QPropertyAnimation::finished, [this](){
        PrepararAnimacionStandBy();
        animacionStandBy->start();
    });

    connect(&emitirDialogo, &QTimer::timeout, this, &NPCUI::Hablar);
    emitirDialogo.setSingleShot(true);

    Mostrandose = false;
}

void NPCUI::Centrar()
{
    int centerX = (padre->width() - width()) /2;
    int centerY = (padre->height() - height());
    move(centerX,centerY);
}

void NPCUI::Entrar()
{
    if (Mostrandose)
        return;

    PrepararAnimacionEntrada();
    animacionEntrada->start();
    this->show();
    emit Entrando();

    if (NPCrepresentado->getDialogo() != ""){
        emitirDialogo.start(random.bounded(1500,3000));
    }
}

void NPCUI::Salir(bool Aceptado)
{
    if (!Mostrandose)
        return;

    animacionStandBy->stop();
    if (emitirDialogo.isActive())
        emitirDialogo.stop();

    if (Aceptado)
        PrepararAnimacionSalida();
    else
        PrepararAnimacionSalida2();

    Mostrandose = false;
    animacionSalida->start();
    emit Saliendo();
}

void NPCUI::PrepararAnimacionEntrada()
{
    int centerX = (padre->width() - width()) / 2;
    int centerY = padre->height() - height();

    animacionEntrada->setStartValue(QPoint(-(width()) -50,centerY+50));
    animacionEntrada->setEndValue(QPoint(centerX,centerY));
}

void NPCUI::PrepararAnimacionSalida()
{
    int SalidaEscena = padre->width() + width();
    int centerY = (padre->height()) - (height()) + 50;

    animacionSalida->setStartValue(pos());
    animacionSalida->setEndValue(QPoint(SalidaEscena,centerY)); // SUMAR LA RESOLUCION DEL WIDGET + EL NPC
}

void NPCUI::PrepararAnimacionSalida2()
{
    int SalidaEscena = -width();
    int centerY = (padre->height()) - (height()) + 50;

    animacionSalida->setStartValue(pos());
    animacionSalida->setEndValue(QPoint(SalidaEscena,centerY));
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
    if (dialogo != "null")
        emit QuiereHablar(dialogo);
}

NPCUI::~NPCUI()
{
    delete animacionEntrada;
    delete animacionSalida;
    delete animacionStandBy;
}

void NPCUI::Pausar(bool Estado)
{
    if (Estado){
        if (!emitirDialogo.isActive())
            return;

        remainingTime = emitirDialogo.remainingTime();
        emitirDialogo.stop();
    } else {
        emitirDialogo.start(remainingTime);
    }
}

void NPCUI::Finalizar()
{
    if (emitirDialogo.isActive())
        emitirDialogo.stop();

    if (Mostrandose)
        this->Salir(true);

    animacionStandBy->stop();
    estadoAnimacionStandby = false;
}

void NPCUI::PrepararAnimacionStandBy()
{
    animacionStandBy->setDuration(random.bounded(300,700));
    int posY = padre->height() - height();
    if (estadoAnimacionStandby){
        animacionStandBy->setStartValue(this->pos());
        animacionStandBy->setEndValue(QPoint(this->x(), posY));
        estadoAnimacionStandby = false;
    } else {
        int sorteo = random.bounded(10);
        if (sorteo < 3) {
            animacionStandBy->setStartValue(this->pos());
            animacionStandBy->setEndValue(QPoint(this->x(), this->y() + random.bounded(5,15)));
        } else {
            animacionStandBy->setStartValue(this->pos());
            animacionStandBy->setEndValue(this->pos());
        }
        estadoAnimacionStandby = true;
    }
}
