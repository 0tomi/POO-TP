#include "globosdialogoui.h"
#include "ui_globosdialogoui.h"

GlobosDialogoUI::GlobosDialogoUI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GlobosDialogoUI)
{
    ui->setupUi(this);
}

GlobosDialogoUI::~GlobosDialogoUI()
{
    delete ui;
}
