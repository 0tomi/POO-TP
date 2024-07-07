#include "ui_npcgenericoui.h"
#include "npcgenericoui.h"
#include <QPixmap>

NPCGenericoUI::NPCGenericoUI(QWidget *parent)
    : NPCUI(parent)
    , ui(new Ui::NPCGenericoUI)
{
    ui->setupUi(this);
    setFixedSize(300,300);
    ui->Cuerpo->setPixmap(QPixmap(":/Resources/NPCs/Cuerpo1.png"));
}

NPCGenericoUI::~NPCGenericoUI()
{
    delete ui;
}

void NPCGenericoUI::setNPC(NPC *newNPCenEscena)
{
    NPCenEscena = newNPCenEscena;
}

