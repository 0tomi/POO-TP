#include "pantallamenu.h"
#include "ui_pantallamenu.h"
#include <QCloseEvent>
PantallaMenu::PantallaMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaMenu)
{
    ui->setupUi(this);
    connect(ui->botonJugar, &QPushButton::clicked, this, &PantallaMenu::botonJugarClicked);
    connect(ui->botonCargar, &QPushButton::clicked, this, &PantallaMenu::botonCargarclicked);
    connect(ui->botonSettings, &QPushButton::clicked, this, &PantallaMenu::botonSettingsclicked);
    connect(ui->botonSalir, &QPushButton::clicked, this, &PantallaMenu::botonSalirclicked);
    connect(ui->botonFacil, &QPushButton::clicked, this, &PantallaMenu::botonFacilclicked);
    connect(ui->botonNormal, &QPushButton::clicked, this, &PantallaMenu::botonNormalclicked);
    connect(ui->botonDemonio, &QPushButton::clicked, this, &PantallaMenu::botonDemonioclicked);
    connect(ui->botonPartida1, &QPushButton::clicked, this, &PantallaMenu::botonPartida1clicked);
    connect(ui->botonPartida2, &QPushButton::clicked, this, &PantallaMenu::botonPartida2clicked);
    connect(ui->botonPartida3, &QPushButton::clicked, this, &PantallaMenu::botonPartida3clicked);
    connect(ui->botonVolver3, &QPushButton::clicked, this, &PantallaMenu::botonVolver3clicked);
    connect(ui->botonVolver2, &QPushButton::clicked, this, &PantallaMenu::botonVolver2clicked);
    connect(ui->botonVolver1, &QPushButton::clicked, this, &PantallaMenu::botonVolver1clicked);
    connect(ui->botonStart, &QPushButton::clicked, this, &PantallaMenu::botonStartclicked);
    ui->menu->setCurrentIndex(0);

}

PantallaMenu::~PantallaMenu()
{
    delete ui;
}

void PantallaMenu::botonJugarClicked()
{
    ui->menu->setCurrentWidget(ui->dificultad);
    emit clickedJugar();
}
void PantallaMenu::botonCargarclicked()
{
    ui->menu->setCurrentWidget(ui->cargar);
    emit clickedCargar();
}

void PantallaMenu::botonSettingsclicked()
{
    emit clickedSettings();
}


void PantallaMenu::botonSalirclicked()
{
    emit clickedSalir(new QCloseEvent);
    qDebug() << "Quiere salir";
}


void PantallaMenu::botonFacilclicked()
{
    ui->menu->setCurrentWidget(ui->descrdificultad);
    ui->descripciones->setCurrentIndex(0);
    dificultad=1;

    emit clickedFacil();
}


void PantallaMenu::botonNormalclicked()
{
    ui->menu->setCurrentWidget(ui->descrdificultad);
    ui->descripciones->setCurrentWidget(ui->page2);
    dificultad=2;

    emit clickedNormal();
}


void PantallaMenu::botonDemonioclicked()
{
    ui->menu->setCurrentWidget(ui->descrdificultad);
    ui->descripciones->setCurrentWidget(ui->page3);
    dificultad=3;

    emit clickedDemonio();
}


void PantallaMenu::botonPartida1clicked()
{
    emit clickedPartida1();
}


void PantallaMenu::botonPartida2clicked()
{
    emit clickedPartida2();
}


void PantallaMenu::botonPartida3clicked()
{
    emit clickedPartida3();
}


void PantallaMenu::botonVolver3clicked()
{
    ui->menu->setCurrentWidget(ui->pprincipal);
}


void PantallaMenu::botonVolver2clicked()
{
 ui->menu->setCurrentWidget(ui->dificultad);
}


void PantallaMenu::botonVolver1clicked()
{
ui->menu->setCurrentWidget(ui->pprincipal);
}


void PantallaMenu::botonStartclicked()
{
    emit clickedStart(1,dificultad);
    qDebug() << "dificultad"<<dificultad;
}

