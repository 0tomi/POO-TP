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
    if (event->button() == Qt::LeftButton) {
        m_dragStartPosition = event->pos();
        raise();
    }
}

void DocumentosUI::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        int dx = event->pos().x() - m_dragStartPosition.x();
        int dy = event->pos().y() - m_dragStartPosition.y();
        move(pos() + QPoint(dx, dy));
    }
}
