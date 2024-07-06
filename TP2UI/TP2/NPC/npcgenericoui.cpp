#include "ui_npcgenericoui.h"
#include "npcgenericoui.h"

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

void NPCGenericoUI::setNPC(NPC *newNPCenEscena)
{
    NPCenEscena = newNPCenEscena;
}

