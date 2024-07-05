#include "documentosui.h"
#include "ui_documentosui.h"
#include <QDebug>
#include <QMouseEvent>

DocumentosUI::DocumentosUI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DocumentosUI)
{
    ui->setupUi(this);
    qDebug() << "Me he manifestado xD";
}

DocumentosUI::~DocumentosUI()
{
    delete ui;
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
