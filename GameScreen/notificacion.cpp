#include "notificacion.h"
#include "ui_notificacion.h"

Notificacion::Notificacion(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Notificacion)
{
    ui->setupUi(this);
}

Notificacion::~Notificacion()
{
    delete ui;
}
