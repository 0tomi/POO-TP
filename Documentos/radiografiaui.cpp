#include "radiografiaui.h"
#include "ui_radiografiaui.h"

radiografiaui::radiografiaui(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::radiografiaui)
{
    ui->setupUi(this);
}

radiografiaui::~radiografiaui()
{
    delete ui;
}
