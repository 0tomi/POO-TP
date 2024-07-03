#include "documento.h"
#include "ui_documento.h"
#include <QMouseEvent>

Documento::Documento(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Documento)
{
    ui->setupUi(this);
}

Documento::~Documento()
{
    delete ui;
}

void Documento::clickIzqEvent(QMouseEvent *event) {
    // Si se preciona el clic izquierdo
    if (event->button() == Qt::LeftButton) {
        // Captamos la posicion del mouse
        m_dragStartPosition = event->pos();
        // Mostramos el widget por encima de los demas
        raise();
    }
}

void Documento::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        // Obtenemos las cordenadas desde donde se esta moviendo el mouse
        int dx = event->pos().x() - m_dragStartPosition.x();
        int dy = event->pos().y() - m_dragStartPosition.y();
        // Movemos el widget a esas posiciones
        move(pos() + QPoint(dx, dy));
    }
}
