#include "pantallamenu.h"
#include "ui_pantallamenu.h"

PantallaMenu::PantallaMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaMenu)
{
    ui->setupUi(this);
    connect(ui->botonJugar, &QPushButton::clicked, this, &PantallaMenu::botonJugarClicked);
    connect(ui->botonSettings, &QPushButton::clicked, this, &PantallaMenu::botonSettingsclicked);
    connect(ui->botonSalir, &QPushButton::clicked, this, &PantallaMenu::botonSalirclicked);
    ui->menu->setCurrentIndex(1);

}

PantallaMenu::~PantallaMenu()
{
    delete ui;
}



void PantallaMenu::botonJugarClicked()
{

}


void PantallaMenu::botonSettingsclicked()
{
    emit clickedSettings();
}


void PantallaMenu::botonSalirclicked()
{
    emit clickedSalir();
}


void PantallaMenu::botonFacilclicked()
{
    emit clickedFacil();
}


void PantallaMenu::botonNormalclicked()
{
    emit clickedNormal();
}


void PantallaMenu::botonDemonioclicked()
{
    emit clickedDemonio();
}

