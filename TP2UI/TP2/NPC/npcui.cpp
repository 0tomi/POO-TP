#include "npcui.h"
#include "ui_npcui.h"

NPCUI::NPCUI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NPCUI)
{
    ui->setupUi(this);
}

NPCUI::~NPCUI()
{
    delete ui;
}
