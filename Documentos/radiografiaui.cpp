#include "radiografiaui.h"
#include "ui_radiografiaui.h"

radiografiaui::radiografiaui(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::radiografiaui)
{
    ui->setupUi(this);
    this->labelsCuerpo[0]=ui->frente1;
    this->labelsCuerpo[1]=ui->frente2;
    this->labelsCuerpo[2]=ui->frente3;
    this->labelsCuerpo[3]=ui->frente4;
    this->labelsCuerpo[4]=ui->frente5;
    this->labelsCuerpo[5]=ui->espalda1;
    this->labelsCuerpo[6]=ui->espalda2;
    this->labelsCuerpo[7]=ui->espalda3;
    this->labelsCuerpo[8]=ui->espalda4;
    this->labelsCuerpo[9]=ui->espalda5;
}

radiografiaui::~radiografiaui()
{
    delete ui;
}
