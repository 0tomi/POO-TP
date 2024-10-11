#include "npcfondo.h"
#include "ui_npcfondo.h"

NPCFondo::NPCFondo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NPCFondo)
{
    ui->setupUi(this);
    padre = parent;
    this->move(QPoint(0, parent->height()));
}

NPCFondo::~NPCFondo()
{
    delete ui;
}
