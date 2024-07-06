#include "npcgenerico.h"
#include "ui_npcgenerico.h"

NPCGenerico::NPCGenerico(QWidget *parent)
    : NPCUI(parent)
    , ui(new Ui::NPCGenerico)
{
    ui->setupUi(this);
    setFixedSize(300,300);

}

NPCGenerico::~NPCGenerico()
{
    delete ui;
}
