#include "documentosui.h"
#include "ui_documentosui.h"
#include <QDebug>
#include <QMouseEvent>

DocumentosUI::DocumentosUI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DocumentosUI)
{
    ui->setupUi(this);

    // Creamos las animaciones de entrada y salida
    animacionEntrada = new QPropertyAnimation(this, "pos");
    animacionSalida = new QPropertyAnimation(this, "pos");

    // Creamos animacion para centrar
    animacionCentrar = new QPropertyAnimation(this, "pos");

    // Hacemos que cuando termine la animacion de salida, el documento desaparezca.
    connect(animacionEntrada, &QPropertyAnimation::finished, this, &DocumentosUI::animacionEntrarTerminada);
    connect(animacionSalida, &QPropertyAnimation::finished, this, &DocumentosUI::hide);

    qDebug() << "Me he manifestado xD";
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
    delete ui;
}

void DocumentosUI::Centrar(int X, int Y)
{
    animacionCentrar->setDuration(500);
    animacionCentrar->setStartValue(pos());
    animacionCentrar->setEndValue(QPoint(X,Y));

    animacionCentrar->start();
}

void DocumentosUI::PrepararAnimacionEntrada(int X, int Y)
{
    animacionEntrada->setDuration(1000);
    animacionEntrada->setStartValue(QPoint(X,-500));
    animacionEntrada->setEndValue(QPoint(X,Y));
}

void DocumentosUI::PrepararAnimacionSalida(int X)
{
    animacionSalida->setDuration(1000);
    animacionSalida->setStartValue(this->pos());
    animacionSalida->setEndValue(QPoint(X,-500));
}

void DocumentosUI::mousePressEvent(QMouseEvent *event) {
    // Si se preciona el clic izquierdo
    if (event->button() == Qt::LeftButton) {
        // Captamos la posicion del mouse
        m_dragStartPosition = event->pos();
        // Mostramos el widget por encima de los demas
        raise();
    }
}

void DocumentosUI::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        // Obtenemos las cordenadas desde donde se esta moviendo el mouse
        int dx = event->pos().x() - m_dragStartPosition.x();
        int dy = event->pos().y() - m_dragStartPosition.y();
        // Movemos el widget a esas posiciones
        move(pos() + QPoint(dx, dy));
    }
}
