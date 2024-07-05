#include "uaderpass.h"
#include "ui_uaderpass.h"

UADERpass::UADERpass(QWidget *parent)
    : DocumentosUI(parent)
    , ui(new Ui::UADERpass)
{
    ui->setupUi(this);
}

UADERpass::~UADERpass()
{
    delete ui;
}
