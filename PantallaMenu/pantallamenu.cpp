#include "pantallamenu.h"
#include "ui_pantallamenu.h"
#include <QCloseEvent>
/// ############################ CONSTRUCTOR ###############################
PantallaMenu::PantallaMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaMenu)
{
    ui->setupUi(this);
    transicion = new PantallaTransicion(this);

    connect(ui->botonJugar, &QPushButton::clicked, this, &PantallaMenu::botonJugarClicked);

    connect(ui->botonFacil, &QPushButton::clicked, this, &PantallaMenu::botonFacilclicked);
    connect(ui->botonNormal, &QPushButton::clicked, this, &PantallaMenu::botonNormalclicked);
    connect(ui->botonDemonio, &QPushButton::clicked, this, &PantallaMenu::botonDemonioclicked);

    connect(ui->botonCargar, &QPushButton::clicked, this, &PantallaMenu::botonCargarclicked);
    connect(ui->botonSettings, &QPushButton::clicked, this, &PantallaMenu::botonSettingsclicked);

    connect(ui->botonPartida1, &QPushButton::clicked, this, &PantallaMenu::botonPartida1clicked);
    connect(ui->botonPartida2, &QPushButton::clicked, this, &PantallaMenu::botonPartida2clicked);
    connect(ui->botonPartida3, &QPushButton::clicked, this, &PantallaMenu::botonPartida3clicked);

    connect(ui->botonSalir, &QPushButton::clicked, this, &PantallaMenu::botonSalirclicked);
    connect(ui->botonVolver1, &QPushButton::clicked, this, &PantallaMenu::botonVolver1clicked);
    connect(ui->botonStart, &QPushButton::clicked, this, &PantallaMenu::botonStartclicked);

    indiceMainMenu = 0;
    indicePrevio = 0;
    ui->BotonesSalir->setCurrentIndex(0);
    ui->menu->setCurrentIndex(0);
}

void PantallaMenu::setInicio()
{
    switchMenu();
}

PantallaMenu::~PantallaMenu()
{
    delete ui;
}

/// ############################ Jugar ###############################
void PantallaMenu::botonJugarClicked()
{
    transicion->ArrancarTransicion(500, this, &PantallaMenu::switchSelectorDificultad);
}

void PantallaMenu::switchSelectorDificultad()
{    
    ui->menu->setCurrentWidget(ui->dificultad);
    ui->BotonesSalir->setCurrentIndex(1);
    emit clickedJugar();
}

/// ############################ Dificultades ###############################
void PantallaMenu::botonFacilclicked()
{
    transicion->ArrancarTransicion(500, this, &PantallaMenu::switchFacil);
}

void PantallaMenu::switchFacil()
{
    ui->menu->setCurrentWidget(ui->descrdificultad);
    ui->descripciones->setCurrentIndex(0);
    dificultad=1;

    emit clickedFacil();
}

void PantallaMenu::botonNormalclicked()
{
    transicion->ArrancarTransicion(500, this, &PantallaMenu::switchNormal);
}

void PantallaMenu::switchNormal()
{
    ui->menu->setCurrentWidget(ui->descrdificultad);
    ui->descripciones->setCurrentWidget(ui->page2);
    dificultad=2;

    emit clickedNormal();
}

void PantallaMenu::botonDemonioclicked()
{
    transicion->ArrancarTransicion(500, this, &PantallaMenu::switchDemonio);
}

void PantallaMenu::switchDemonio()
{
    ui->menu->setCurrentWidget(ui->descrdificultad);
    ui->descripciones->setCurrentWidget(ui->page3);
    dificultad=3;

    emit clickedDemonio();
}
/// ############################ Empezar a jugar ###############################
void PantallaMenu::botonStartclicked()
{
    emit clickedStart(1,dificultad);
    qDebug() << "dificultad"<<dificultad;
}
/// ############################ Cargar partida ###############################
void PantallaMenu::botonCargarclicked()
{
    transicion->ArrancarTransicion(700, this, &PantallaMenu::switchCargar);
}

void PantallaMenu::switchCargar()
{
    ui->menu->setCurrentWidget(ui->cargar);
    ui->BotonesSalir->setCurrentIndex(1);
    emit clickedCargar();
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

/// ############################ Opciones ###############################
void PantallaMenu::botonSettingsclicked()
{
    emit clickedSettings();
}

/// ############################ Salir ###############################
void PantallaMenu::botonSalirclicked()
{
    emit clickedSalir();
    qDebug() << "Quiere salir";
}

/// ############################ Volver ###############################
void PantallaMenu::botonVolver1clicked()
{
    int indiceActual = ui->menu->currentIndex();
    switch (indiceActual){
    case 1: // cargar partida
        transicion->ArrancarTransicion(500, this, &PantallaMenu::switchMenu);
        break;
    case 2: // Selector de dificultad
        transicion->ArrancarTransicion(500, this, &PantallaMenu::switchMenu);
        break;
    case 3: // Descripcion de dificultad
        transicion->ArrancarTransicion(500, this, &PantallaMenu::switchSelectorDificultad);
        break;
    }

}

void PantallaMenu::switchMenu()
{
    ui->menu->setCurrentIndex(0);
    ui->BotonesSalir->setCurrentIndex(0);
}

