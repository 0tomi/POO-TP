#include "npcui.h"
#include "ui_npcui.h"

NPCUI::NPCUI(QWidget *parent)
    : QWidget(parent)
{
    padre = parent;

    // Preparamos animaciones de entrada del NPC
    animacionEntrada = new QPropertyAnimation(this, "pos");
    animacionEntrada->setDuration(1000);
    animacionEntrada->setEasingCurve(QEasingCurve::OutQuad);    // La animacion se desacelera conforme entra

    // Preparamos animaciones de salida del NPC
    animacionSalida = new QPropertyAnimation(this, "pos");
    animacionSalida->setDuration(1500);
    animacionSalida->setEasingCurve(QEasingCurve::InQuad);  // La animacion se acelera conforme sale

    connect(animacionSalida, &QPropertyAnimation::finished, this, &NPCUI::TerminoAnimacion);
    connect(animacionEntrada, &QPropertyAnimation::finished, [this](){
        emit animacionEntrarTerminada();
        Mostrandose = true;
    });
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
    PrepararAnimacionEntrada();
    animacionEntrada->start();
    this->show();
    emit Entrando();
    if (NPCrepresentado->getDialogo() != ""){
        connect(&emitirDialogo, &QTimer::timeout, this, &NPCUI::Hablar);
        emitirDialogo.start(1500);
    }
}

void NPCUI::PrepararAnimacionEntrada()
{
    int centerX = (padre->width() - width()) / 2;
    int centerY = padre->height() - height();

    animacionEntrada->setStartValue(QPoint(-(width()) -50,centerY+50));
    animacionEntrada->setEndValue(QPoint(centerX,centerY));
}


void NPCUI::Sacar()
{
    PrepararAnimacionSalida();
    Mostrandose = false;
    animacionSalida->start();
    disconnect(&emitirDialogo, &QTimer::timeout, this, &NPCUI::Hablar);
    emit Saliendo();
}

void NPCUI::PrepararAnimacionSalida()
{
    int SalidaEscena = padre->width() + width();
    int centerY = (padre->height()) - (height()) + 50;

    animacionSalida->setStartValue(pos());
    animacionSalida->setEndValue(QPoint(SalidaEscena,centerY)); // SUMAR LA RESOLUCION DEL WIDGET + EL NPC
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

void NPCUI::moveEvent(QMoveEvent *event)
{
    if (Mostrandose)
        this->Centrar();
    else
        QWidget::moveEvent(event);
}
