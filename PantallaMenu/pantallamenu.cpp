#include "pantallamenu.h"
#include "ui_pantallamenu.h"
#include <QCloseEvent>
/// ############################ CONSTRUCTOR ###############################
PantallaMenu::PantallaMenu(ActivarCheats tipo, GuardarPartidas * gp, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaMenu), GTALocura(this), SonidosBotones(parent), SonidoModoDemonio(parent), Musica(parent), dificultad(1), nivel(1)
    , MusicaCreditos(this)
{
    ui->setupUi(this);
    this->guardarPartida = gp;
    this->ConfigurarSonidos();

    transicion = new PantallaTransicion(this);

    connect(ui->botonJugar, &QPushButton::clicked, this, &PantallaMenu::botonJugarClicked);
    connect(ui->tutorialButton, &QPushButton::clicked, this, &PantallaMenu::clickedTutorial);

    this->ConfigurarBotonesDificultad();

    connect(ui->botonCargar, &QPushButton::clicked, this, &PantallaMenu::botonCargarclicked);
    connect(ui->botonSettings, &QPushButton::clicked, this, &PantallaMenu::botonSettingsclicked);

    this->ConfigurarBotonesElegirPartidaGuardada();

    connect(ui->botonSalir, &QPushButton::clicked, this, &PantallaMenu::botonSalirclicked);
    connect(ui->botonVolver1, &QPushButton::clicked, this, &PantallaMenu::botonVolver1clicked);
    connect(ui->botonStart, &QPushButton::clicked, this, &PantallaMenu::botonStartclicked);

    connect(ui->botonCheat, &QPushButton::clicked, [this]() {
        transicion->ArrancarTransicion(500, this, &PantallaMenu::switchCheatClicked);
    });

    connect(ui->SeleccionarDificultad, &QSpinBox::valueChanged, this, &PantallaMenu::actualizarDificultad);
    connect(ui->SeleccionarNivel, &QSpinBox::valueChanged, this, &PantallaMenu::actualizarNivel);
    connect(ui->SeleccionarSeed, &QSpinBox::valueChanged, [this](int newSeed){this->seedPersonalizada = newSeed;});

    connect(ui->cheatPlayClicked, &QPushButton::clicked, this, &PantallaMenu::cheatStartClicked);
    connect(ui->botonCreditos, &QPushButton::clicked, this, &PantallaMenu::clickedCreditos);

    this->ConfigurarBotonesElegirRanura();

    indiceMainMenu = 0;
    indicePrevio = 0;

    if (tipo == Activado){
        ui->botonCheat->show();
        CheatsActivados = true;
    } else ui->botonCheat->hide();

    ui->BotonesSalir->setCurrentIndex(0);
    ui->menu->setCurrentIndex(0);

    Musica.play();
}

void PantallaMenu::ConfigurarSonidos()
{
    GTALocura.setSource(QUrl("qrc:/Resources/Sonidos/NotificacionGTA.wav"));
    SonidosBotones.setSource(QUrl("qrc:/Resources/Sonidos/BotonesMenu.WAV"));
    SonidoModoDemonio.setSource(QUrl("qrc:/Resources/Sonidos/ModoDemonioBoton.WAV"));
    Musica.setSource(QUrl("qrc:/Resources/Musica/MenuMusica.WAV"));
    setMusicVolume(0.5);
    setVolumen(1.0);
    GTALocura.setVolume(1.0);
    Musica.setLoopCount(QSoundEffect::Infinite);
    MusicaCreditos.setSource(QUrl("qrc:/Resources/Musica/MusicaJuego6.WAV"));
    MusicaCreditos.setLoopCount(QSoundEffect::Infinite);
    MusicaCreditos.setVolume(0.3);
}

void PantallaMenu::ConfigurarBotonesDificultad()
{
    connect(ui->botonFacil, &QPushButton::clicked, this, &PantallaMenu::botonFacilclicked);
    connect(ui->botonNormal, &QPushButton::clicked, this, &PantallaMenu::botonNormalclicked);
    connect(ui->botonDemonio, &QPushButton::clicked, this, &PantallaMenu::botonDemonioclicked);
}

void PantallaMenu::ConfigurarBotonesElegirPartidaGuardada()
{
    connect(ui->botonPartida1, &QPushButton::clicked, this, &PantallaMenu::botonPartida1clicked);
    connect(ui->botonPartida2, &QPushButton::clicked, this, &PantallaMenu::botonPartida2clicked);
    connect(ui->botonPartida3, &QPushButton::clicked, this, &PantallaMenu::botonPartida3clicked);
}

void PantallaMenu::ConfigurarBotonesElegirRanura()
{
    connect(ui->boton_Ranura1, &QPushButton::clicked, [this](){this->SlotGuardadoSeleccionado(0);});
    connect(ui->boton_Ranura2, &QPushButton::clicked, [this](){this->SlotGuardadoSeleccionado(1);});
    connect(ui->boton_Ranura3, &QPushButton::clicked, [this](){this->SlotGuardadoSeleccionado(2);});
    connect(ui->AceptarSobreescribir, &QPushButton::clicked, [this](){SonidosBotones.play(); emit clickedStartDefault(this->dificultad);});
}

void PantallaMenu::setInicio()
{
    switchMenu();
}

PantallaMenu::~PantallaMenu()
{
    delete ui;
}

void PantallaMenu::stopMusic()
{
    Musica.stop();
}

void PantallaMenu::continueMusic()
{
    Musica.play();
}

void PantallaMenu::checkSaveSlots()
{
    Partidas = guardarPartida->LeerPartidas();
    bloquearBotonGuardado(ui->botonPartida1, ui->boton_Ranura1);
    bloquearBotonGuardado(ui->botonPartida2, ui->boton_Ranura2);
    bloquearBotonGuardado(ui->botonPartida3, ui->boton_Ranura3);
    for (int i = 0; i < 3; i++)
        setBotonesPartida(i, Partidas[i]);
}

void PantallaMenu::setBotonesPartida(int num, bool estado)
{
    if (!estado)
        return;

    if (num == 0)
        desbloquearBotonGuardado(ui->botonPartida1, ui->boton_Ranura1);
    if (num == 1)
        desbloquearBotonGuardado(ui->botonPartida2, ui->boton_Ranura2);
    if (num == 2)
        desbloquearBotonGuardado(ui->botonPartida3, ui->boton_Ranura3);
}

void PantallaMenu::bloquearBotonGuardado(QPushButton * botonGuardado, QPushButton * botonRanura)
{
    botonGuardado->setDisabled(true);
    botonGuardado->setStyleSheet(COLOR_BLOQUEADO);
    botonRanura->setStyleSheet(COLOR_BLOQUEADO);
}

void PantallaMenu::desbloquearBotonGuardado(QPushButton * botonGuardado, QPushButton * botonRanura)
{
    botonGuardado->setEnabled(true);
    botonGuardado->setStyleSheet(COLOR_DESBLOQUEADO);
    botonRanura->setStyleSheet(COLOR_DESBLOQUEADO);
}

void PantallaMenu::setVolumen(float vol)
{
    SonidosBotones.setVolume(vol);
    SonidoModoDemonio.setVolume(vol);
}

void PantallaMenu::setMusicVolume(float vol)
{
    Musica.setVolume(vol-0.4);
    MusicaCreditos.setVolume(vol-0.4);
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
    SonidosBotones.play();
    ui->menu->setCurrentWidget(ui->CheatPage);
}

/// ############################ Jugar ###############################
void PantallaMenu::botonJugarClicked()
{
    SonidosBotones.play();
    transicion->ArrancarTransicion(500, this, &PantallaMenu::switchSelectorDificultad);
}

void PantallaMenu::switchSelectorDificultad()
{
    ui->menu->setCurrentWidget(ui->dificultad);
    ui->BotonesSalir->setCurrentIndex(1);
    nivel = 1;
    emit clickedJugar();
}

/// ############################ Dificultades ###############################
void PantallaMenu::botonFacilclicked()
{
    SonidosBotones.play();
    transicion->ArrancarTransicion(500, this, &PantallaMenu::switchFacil);
    this->dificultad=1;
}

void PantallaMenu::switchFacil()
{
    ui->menu->setCurrentWidget(ui->descrdificultad);
    ui->descripciones->setCurrentIndex(0);

    emit clickedFacil();
}

void PantallaMenu::botonNormalclicked()
{
    SonidosBotones.play();
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
    SonidoModoDemonio.play();
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
    SonidosBotones.play();
    transicion->ArrancarTransicion(500, [this](){ui->menu->setCurrentIndex(5);});
}

void PantallaMenu::cheatStartClicked()
{
    emit EnviarLogs("Nivel: " + QString::number(this->nivel) + " | Dificultad: " + QString::number(this->dificultad) + " | Seed: " + QString::number(this->seedPersonalizada));
    emit clickedStartCheat(this->nivel, this->dificultad, this->seedPersonalizada);
}

void PantallaMenu::SlotGuardadoSeleccionado(int numero)
{
    SonidosBotones.play();
    emit EnviarLogs("Slot de guardado seleccionado: " + QString::number(numero));
    emit EnviarLogs("Nivel: 1 | Dificultad: " + QString::number(dificultad));
    emit slotSelected2Save(numero);
    if (Partidas[numero])
        ui->menu->setCurrentWidget(ui->ConfirmarSobreescribir);
    else
        emit clickedStartDefault(this->dificultad);
}

/// ############################ Cargar partida ###############################
void PantallaMenu::botonCargarclicked()
{
    SonidosBotones.play();
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
    emit EnviarLogs("Slot de partida 1 apretado");
    SonidosBotones.play();
    emit slotSelected2Play(0);
}

void PantallaMenu::botonPartida2clicked()
{
    emit EnviarLogs("Slot de partida 2 apretado");
    SonidosBotones.play();
    emit slotSelected2Play(1);
}

void PantallaMenu::botonPartida3clicked()
{
    emit EnviarLogs("Slot de partida 3 apretado");
    SonidosBotones.play();
    emit slotSelected2Play(2);
}

/// ############################ Opciones ###############################
void PantallaMenu::botonSettingsclicked()
{
    emit EnviarLogs ("Abriendo Settings");
    SonidosBotones.play();
    emit clickedSettings();
}

/// ############################ Salir ###############################
void PantallaMenu::botonSalirclicked()
{
    emit EnviarLogs ("Quiere salir");
    SonidosBotones.play();
    emit clickedSalir();
}

/// ############################ Volver ###############################
void PantallaMenu::botonVolver1clicked()
{
    SonidosBotones.play();
    int indiceActual = ui->menu->currentIndex();
    switch (indiceActual){
    case 1: // cargar partida
        transicion->ArrancarTransicion(500, this, &PantallaMenu::switchMenu);
        break;
    case 2: // Selector de dificultad
        transicion->ArrancarTransicion(500, this, &PantallaMenu::switchMenu);
        break;
    case 6: ui->menu->setCurrentIndex(5);
        break;
    case 7: MusicaCreditos.stop();
        transicion->ArrancarTransicion(500, this, &PantallaMenu::switchMenu);
        break;
    default: // Descripcion de dificultad, Cheat mode, Seleccionar slot de guardado
        transicion->ArrancarTransicion(500, this, &PantallaMenu::switchSelectorDificultad);
        break;
    }

}

void PantallaMenu::switchMenu()
{
    if (!Musica.isPlaying())
        Musica.play();

    ui->menu->setCurrentIndex(0);
    ui->BotonesSalir->setCurrentIndex(0);
}


void PantallaMenu::tutorialButton()
{
    emit EnviarLogs("Se clickeo la pantalla Tutorial");
    SonidosBotones.play();
    emit clickedTutorial();
}

void PantallaMenu::clickedCreditos()
{
    Musica.stop();
    transicion->ArrancarTransicion(500, [this](){
        ui->BotonesSalir->setCurrentIndex(1);
        ui->menu->setCurrentWidget(ui->Creditos);
        MusicaCreditos.play();
    });
}

