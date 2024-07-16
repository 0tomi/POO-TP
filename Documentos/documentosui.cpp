#include "documentosui.h"
#include "ui_documentosui.h"
#include <QDebug>
#include <QMouseEvent>

DocumentosUI::DocumentosUI(QWidget *parent)
    : QWidget(parent)
{
    // Creamos las animaciones de entrada
    animacionEntrada = new QPropertyAnimation(this, "pos");
    animacionEntrada->setDuration(1000);
    animacionEntrada->setEasingCurve(QEasingCurve::OutExpo);

    // Creamos las animaciones de salida
    animacionSalida = new QPropertyAnimation(this, "pos");
    animacionSalida->setDuration(1000);
    animacionSalida->setEasingCurve(QEasingCurve::InExpo);

    // Creamos animacion para centrar
    animacionCentrar = new QPropertyAnimation(this, "pos");
    animacionCentrar->setDuration(1000);
    animacionCentrar->setEasingCurve(QEasingCurve::OutQuad);

    // Hacemos que cuando termine la animacion de salida, el documento desaparezca.
    connect(animacionEntrada, &QPropertyAnimation::finished, this, &DocumentosUI::animacionEntrarTerminada);
    connect(animacionSalida, &QPropertyAnimation::finished, this, &DocumentosUI::hide);
}

void DocumentosUI::Entrar(int X, int Y)
{
    this->PrepararAnimacionEntrada(X,Y);
    this->show();
    this->animacionEntrada->start();
}

void DocumentosUI::Sacar(int X)
{
    this->PrepararAnimacionSalida(X);
    this->animacionSalida->start();
}

DocumentosUI::~DocumentosUI()
{
    delete animacionCentrar;
    delete animacionEntrada;
    delete animacionSalida;
}

void DocumentosUI::Centrar(int X, int Y)
{
    if (animacionCentrar->state() == QAbstractAnimation::Paused)
        animacionCentrar->stop();

    animacionCentrar->setStartValue(pos());
    animacionCentrar->setEndValue(QPoint(X,Y));

    animacionCentrar->start();
}

void DocumentosUI::PausarAnimacionCentrar()
{
    if (animacionCentrar->state() == QAbstractAnimation::Running)
        animacionCentrar->pause();
}

void DocumentosUI::PrepararAnimacionEntrada(int X, int Y)
{
    if (animacionEntrada->state() == QAbstractAnimation::Paused)
        animacionEntrada->stop();

    animacionEntrada->setStartValue(QPoint(X,-500));
    animacionEntrada->setEndValue(QPoint(X,Y));
}

void DocumentosUI::PrepararAnimacionSalida(int X)
{
    animacionSalida->setStartValue(this->pos());
    animacionSalida->setEndValue(QPoint(X,-500));
}

void DocumentosUI::mousePressEvent(QMouseEvent *event) {
    // Si se preciona el clic izquierdo
    if (event->button() == Qt::LeftButton) {
        // Frenamos la animacion de centrar o entrar
        if (animacionCentrar->state() == QAbstractAnimation::Running)
            animacionCentrar->pause();
        if (animacionEntrada->state() == QAbstractAnimation::Running)
            animacionEntrada->pause();
        // Captamos la posicion del mouse
        m_dragStartPosition = event->pos();
        // Mostramos el widget por encima de los demas
        raise();
    }
}

void DocumentosUI::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        if (animacionSalida->state() == QAbstractAnimation::Running)
            return;
        // Obtenemos las cordenadas desde donde se esta moviendo el mouse
        int dx = event->pos().x() - m_dragStartPosition.x();
        int dy = event->pos().y() - m_dragStartPosition.y();
        // Movemos el widget a esas posiciones
        move(pos() + QPoint(dx, dy));
    }
}
