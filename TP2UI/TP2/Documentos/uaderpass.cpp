#include "uaderpass.h"
#include "ui_uaderpass.h"
#include <QDebug>

UADERpass::UADERpass(QWidget *parent)
    : DocumentosUI(parent)
    , ui(new Ui::UADERpass)
{
    ui->setupUi(this);
}

void UADERpass::setDocumentacionInfo(Documentacion *documento)
{
    qDebug() << "xD";
}

UADERpass::~UADERpass()
{
    delete ui;
}
