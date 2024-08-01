#include "pantallamenu.h"
#include "ui_pantallamenu.h"
#include <QCloseEvent>
/// ############################ CONSTRUCTOR ###############################
PantallaMenu::PantallaMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaMenu), GTALocura(this)
{
    ui->setupUi(this);
    GTALocura.setSource(QUrl("qrc:/Resources/Sonidos/NotificacionGTA.wav"));
    GTALocura.setVolume(1.0);

    transicion = new PantallaTransicion(this);

    connect(ui->botonJugar, &QPushButton::clicked, this, &PantallaMenu::botonJugarClicked);

    connect(ui->tutorialButton, &QPushButton::clicked, this, &PantallaMenu::clickedTutorial);

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

    connect(ui->botonCheat, &QPushButton::clicked, [this]() {
        transicion->ArrancarTransicion(500, this, &PantallaMenu::switchCheatClicked);
    });

    connect(ui->SeleccionarDificultad, &QSpinBox::valueChanged, this, &PantallaMenu::actualizarDificultad);
    connect(ui->SeleccionarNivel, &QSpinBox::valueChanged, this, &PantallaMenu::actualizarNivel);

    connect(ui->cheatPlayClicked, &QPushButton::clicked, this, &PantallaMenu::botonStartclicked);

    indiceMainMenu = 0;
    indicePrevio = 0;

    ui->botonCheat->hide();

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

void PantallaMenu::keyPressEvent(QKeyEvent *event)
{
    if (!CheatsActivados){
        bool TeclaIncorrecta = true;
        if (SecuenciaMagica == 0 && event->key() == Qt::Key_H)
            ActualizarCont(SecuenciaMagica, TeclaIncorrecta);
        if (SecuenciaMagica == 1 && event->key() == Qt::Key_E)
            ActualizarCont(SecuenciaMagica, TeclaIncorrecta);
        if (SecuenciaMagica == 2 && event->key() == Qt::Key_S)
           ActualizarCont(SecuenciaMagica, TeclaIncorrecta);
        if (SecuenciaMagica == 3 && event->key() == Qt::Key_O)
            ActualizarCont(SecuenciaMagica, TeclaIncorrecta);
        if (SecuenciaMagica == 4 && event->key() == Qt::Key_Y)
            ActualizarCont(SecuenciaMagica, TeclaIncorrecta);
        if (SecuenciaMagica == 5 && event->key() == Qt::Key_A)
            ActualizarCont(SecuenciaMagica, TeclaIncorrecta);
        if (SecuenciaMagica == 6 && event->key() == Qt::Key_M)
            ActualizarCont(SecuenciaMagica, TeclaIncorrecta);

        if (TeclaIncorrecta)
            SecuenciaMagica = 0;
        else if (SecuenciaMagica == 7)
            DesbloquearCheats();
    }
    QWidget::keyPressEvent(event);
}

void PantallaMenu::ActualizarCont(int &Contador, bool &Bool)
{
    Contador++;
    Bool = false;
}

void PantallaMenu::DesbloquearCheats()
{
    GTALocura.play();
    CheatsActivados = true;
    ui->botonCheat->show();
}

void PantallaMenu::actualizarNivel(int newNivel)
{
    nivel = newNivel;
}

void PantallaMenu::actualizarDificultad(int newDif)
{
    dificultad = newDif;
}

void PantallaMenu::switchCheatClicked()
{
    ui->menu->setCurrentWidget(ui->CheatPage);
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
    nivel = 1;
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
    nivel = 1;
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
    nivel = 1;
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
    emit clickedStart(nivel,dificultad);
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
    case 4: // Cheat mode
        transicion->ArrancarTransicion(500, this, &PantallaMenu::switchSelectorDificultad);
        break;
    }

}

void PantallaMenu::switchMenu()
{
    ui->menu->setCurrentIndex(0);
    ui->BotonesSalir->setCurrentIndex(0);
}


void PantallaMenu::tutorialButton()
{
    emit clickedTutorial();
}

