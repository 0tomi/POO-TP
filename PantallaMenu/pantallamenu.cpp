#include "pantallamenu.h"
#include "ui_pantallamenu.h"

PantallaMenu::PantallaMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaMenu)
{
    ui->setupUi(this);
}

PantallaMenu::~PantallaMenu()
{
    delete ui;
}

void PantallaMenu::on_botonCargar_clicked()
{

}

