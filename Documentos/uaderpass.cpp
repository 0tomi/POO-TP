#include "uaderpass.h"
#include "ui_uaderpass.h"
#include <QDebug>

UADERpass::UADERpass(QWidget *parent)
    : DocumentosUI(parent)
    , ui(new Ui::UADERpass)
{
    ui->setupUi(this);
    setFixedSize(150,150);
}

void UADERpass::setDocumentacionInfo(Documentacion *documento)
{
    qDebug() << "xD";
}

void UADERpass::Entrar()
{
    DocumentosUI::Entrar();
    raise();
}

UADERpass::~UADERpass()
{
    delete ui;
}
