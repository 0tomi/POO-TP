#include "ui_npcgenericoui.h"
#include "npcgenericoui.h"
#include <QPixmap>

NPCGenericoUI::NPCGenericoUI(QWidget *parent)
    : NPCUI(parent)
    , ui(new Ui::NPCGenericoUI)
{
    ui->setupUi(this);
    setFixedSize(300,300);
}

NPCGenericoUI::~NPCGenericoUI()
{
    delete ui;
}

void NPCGenericoUI::setNPC(NPCcomun *newNPCenEscena)
{
    NPCenEscena = newNPCenEscena;

    ui->Cuerpo->setPixmap(QPixmap(NPCenEscena->getCaraURL()));
    ui->Boca->setPixmap(QPixmap(NPCenEscena->getBocaURL()));
    ui->Ojos->setPixmap(QPixmap(NPCenEscena->getOjosURL()));
    ui->Cejas->setPixmap(QPixmap(NPCenEscena->getCejasURL()));
    ui->Nariz->setPixmap(QPixmap(NPCenEscena->getNarizURL()));
}

