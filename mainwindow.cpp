#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

/// ############################### CONSTRUCTOR #######################################
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), guardarPartida(), log(Logs::Activado)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/Resources/th.jpeg"));
    setWindowTitle("Trabajo practico de POO");

    CrearPantallasJuego();

    ConexionesPantallaPausa();
    ConexionesPantallaMenu();
    ConexionesPantallaEstadisticas();
    ConexionesPantallaGameScreen();
    ConexionesLogs();

    // Mostrar en pantalla completa:
    this->showFullScreen();
    pantallaPausa->setWindowedButton();

    // Hacemos que al cambiar de pantalla, la pantalla que se muestre sea el nuevo foco.
    pantallaMenu->setFocus();
    connect(pantallas, &QStackedWidget::currentChanged, [this](){
        QWidget * pantallaActual = pantallas->currentWidget();
        pantallaActual->setFocus(); // polimorfismo locura
    });
}

MainWindow::~MainWindow()
{
    delete ui;
    delete juego;
    delete pantallaMenu;
    delete pantallaPausa;
    delete pantallaFinalNivel;
    delete gameScreen;
    delete transicion;
    delete pantallas;
    // aca iria el delete a las pantallas
}

/// ############################### PANTALLAS DE LA APLICACION #######################################
void MainWindow::CrearPantallasJuego()
{
    // Iniciamos la logica del juego
    juego = new Juego();

    // Seteamos el widget donde se acomodaran las distintas pantallas del juego
    pantallas = new QStackedWidget(this);
    setCentralWidget(pantallas);

    // Creamos las pantallas del juego
    pantallaMenu = new PantallaMenu(PantallaMenu::Desactivado, &guardarPartida, this);
    gameScreen = new GameScreen(juego, this);
    pantallaPausa = new PantallaPausa(this);
    pantallaFinalNivel = new PantallaFinalNivel(&guardarPartida, this);
    transicion = new PantallaTransicion(this);
    // Tutorial
    pantallaTutorial = new PantallaTutorial(this);
    connect(pantallaTutorial, &PantallaTutorial::TerminarTutorial, this, &MainWindow::PrepararSalirTutorial);

    // Añadimos las pantallas al stack
    pantallas->addWidget(pantallaMenu);
    pantallas->addWidget(gameScreen);
    pantallas->addWidget(pantallaPausa);
    pantallas->addWidget(pantallaFinalNivel);
    pantallas->addWidget(pantallaTutorial);

    // Mostramos la pantalla de inicio
    setInicio();
}

/// ################################### CONEXIONES DE PANTALLAS #######################################
void MainWindow::ConexionesPantallaPausa()
{
    // Conectamos las señales del menu de pausa
    connect(pantallaPausa, &PantallaPausa::setFullScreen, this, &MainWindow::showFullScreen);
    connect(pantallaPausa, &PantallaPausa::setWindowedScreen, this, &MainWindow::PonerModoVentana);
    connect(pantallaPausa, &PantallaPausa::return2lastWidget, this, &MainWindow::PrepararSalirPantallaPausa);
    connect(pantallaPausa, &PantallaPausa::quit, this, &MainWindow::VolverInicio);
    connect(pantallaPausa, &PantallaPausa::clickedTutorial, this, &MainWindow::PrepararTutorial);
    connect(pantallaPausa, &PantallaPausa::soundVolume, gameScreen , &GameScreen::setVolumenes);
    connect(pantallaPausa, &PantallaPausa::musicVolume, gameScreen, &GameScreen::setMusicVolume);
    connect(pantallaPausa, &PantallaPausa::soundVolume, pantallaMenu , &PantallaMenu::setVolumen);
    connect(pantallaPausa, &PantallaPausa::musicVolume, pantallaMenu, &PantallaMenu::setMusicVolume);
    connect(pantallaPausa, &PantallaPausa::soundVolume, pantallaFinalNivel , &PantallaFinalNivel::setSoundVolume);
    connect(pantallaPausa, &PantallaPausa::musicVolume, pantallaFinalNivel, &PantallaFinalNivel::setMusicVolume);
    connect(pantallaPausa, &PantallaPausa::soundVolume, pantallaTutorial , &PantallaTutorial::setSoundVolume);
    connect(pantallaPausa, &PantallaPausa::musicVolume, pantallaTutorial, &PantallaTutorial::setMusicVolume);
}

void MainWindow::ConexionesPantallaMenu()
{
    // Cuando se clickee jugar, abrimos el juego:
    connect(pantallaMenu, &PantallaMenu::clickedStartDefault, [this](int dif){this->TransicionJuego(1,dif);});
    connect(pantallaMenu, &PantallaMenu::clickedStart, this, &MainWindow::TransicionJuego);
    connect(pantallaMenu, &PantallaMenu::clickedSettings, this, &MainWindow::PrepararPantallaPausa);
    connect(pantallaMenu, &PantallaMenu::clickedSalir, this, &MainWindow::close);
    connect(pantallaMenu, &PantallaMenu::clickedTutorial, this, &MainWindow::PrepararTutorial);
    connect(pantallaMenu, &PantallaMenu::slotSelected2Save, [this](int slot){
        guardarPartida.setCurrentSlot(slot);
    });
    connect(pantallaMenu, &PantallaMenu::slotSelected2Play, [this](int slot){
        auto Save = guardarPartida.CargarPartida(slot);
        guardarPartida.setCurrentSlot(slot);
        TransicionJuegoConSave(Save);
    });
    connect(pantallaMenu, &PantallaMenu::clickedStartCheat, this, &MainWindow::TransicionJuegoCheat);
}

void MainWindow::ConexionesPantallaEstadisticas()
{
    connect(pantallaFinalNivel, &PantallaFinalNivel::salirClicked, this, &MainWindow::VolverInicio);
    connect(pantallaFinalNivel, &PantallaFinalNivel::sigNivelClicked, this, &MainWindow::TransicionJuego);
    connect(pantallaFinalNivel, &PantallaFinalNivel::reintentarClicked, this, &MainWindow::TransicionJuego);
}

void MainWindow::ConexionesPantallaGameScreen()
{
    // Conectamos el final de la partida con el nivel terminado
    connect(gameScreen, &GameScreen::NivelTerminado, this, &MainWindow::PrepararPantallaFinalNivel);
    connect(gameScreen, &GameScreen::Guardar, [this](PlayerStats &stats){
        guardarPartida.saveCurrentSlot(stats);
    });
}
/// ################################## PANTALLA DE ESTADISTICAS #############################################

void MainWindow::PrepararPantallaFinalNivel(bool Perdio)
{
    transicion->ArrancarTransicion(1000, this, &MainWindow::setPantallaStats);
    pantallaFinalNivel->setPantallaFinalUI(juego, Perdio);

    // Si perdio, reseteamos las estadisticas para que pueda volver a jugar
    if (Perdio)
        gameScreen->Restart();
}

void MainWindow::setPantallaStats()
{
    pantallas->setCurrentWidget(pantallaFinalNivel);
}

/// ################################## EVENTOS DE LA MAINWINDOW #############################################

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_F11) {
        if (this->isFullScreen()) {
            PonerModoVentana();
            pantallaPausa->setFullScreenButton();   // Hacemos que en el menu de pausa se muestre el boton de poner en pantalla completa
        } else {
            // Cambia a modo pantalla completa si no lo está
            pantallaPausa->setWindowedButton();   // Hacemos que en el menu de pausa se muestre el boton de poner en ventana
            this->showFullScreen();
        }
    }
    if (event->key() == Qt::Key_Escape){
        if (pantallas->currentWidget() != pantallaPausa)
            PrepararPantallaPausa();
        else
            PrepararSalirPantallaPausa();
    }
    QMainWindow::keyPressEvent(event);  // Llama al método base para manejar otros eventos de teclado
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // Mostrar un mensaje de confirmación
    QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Cerrar Juego",
                                                               "¿Estás seguro de que quieres cerrar el Juego?",
                                                               QMessageBox::No | QMessageBox::Yes,
                                                               QMessageBox::Yes);
    if (resBtn == QMessageBox::Yes) {
        event->accept();  // Aceptar el evento y cerrar la ventana
        log.SaveLogs();
        QApplication::quit();  // Cerrar la aplicación
    } else {
        event->ignore();  // Ignorar el evento y no cerrar la ventana
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    this->transicion->resize(this->size());
}

/// ################################## PANTALLA DE JUEGO #############################################

void MainWindow::TransicionJuego(int Nivel, int Dificultad)
{
    pantallaMenu->stopMusic();
    this->nivel = Nivel; this->dificultad = Dificultad;
    transicion->ArrancarTransicionCargando(1000, [this](){
        gameScreen->PrepararJuego(nivel, dificultad);
        pantallas->setCurrentWidget(gameScreen);
    });

    // Conectamos el final de la animacion, para mostrar la ventana del juego.
    connect(transicion, &PantallaTransicion::terminoAnimacion, this, &MainWindow::IniciarJuego);
}

void MainWindow::TransicionJuegoConSave(PlayerStats &datos)
{
    pantallaMenu->stopMusic();
    this->stats = datos;
    transicion->ArrancarTransicionCargando(1000, [this](){
        gameScreen->PrepararJuego(this->stats);
        pantallas->setCurrentWidget(gameScreen);
    });

    // Conectamos el final de la animacion, para mostrar la ventana del juego.
    connect(transicion, &PantallaTransicion::terminoAnimacion, this, &MainWindow::IniciarJuego);
}

void MainWindow::TransicionJuegoCheat(int lvl, int dif, quint32 seed)
{
    pantallaMenu->stopMusic();
    this->nivel = lvl; this->dificultad = dif; this->seedPersonalizada = seed;
    transicion->ArrancarTransicionCargando(1000, [this](){
        gameScreen->PrepararJuegoCheat(nivel, dificultad, seedPersonalizada);
        pantallas->setCurrentWidget(gameScreen);
    });

    // Conectamos el final de la animacion, para mostrar la ventana del juego.
    connect(transicion, &PantallaTransicion::terminoAnimacion, this, &MainWindow::IniciarJuego);
}

void MainWindow::IniciarJuego()
{
    // Desconectamos la animacion para poder usar despues la pantalla de transicion
    disconnect(transicion, &PantallaTransicion::terminoAnimacion, this, &MainWindow::IniciarJuego);
    gameScreen->Iniciar(); // Aca dsps iria el nivel de juego que toca.
}

/// ################################## PANTALLA DE INICIO #############################################
void MainWindow::VolverInicio()
{
    if (PantallaPrevia == 1){
        // Hacemos que termine el nivel pero no que muestre la pantalla de final de nivel.
        gameScreen->FinalDePartida();
    }
    transicion->ArrancarTransicion(1000, this, &MainWindow::setInicio);
}

void MainWindow::setInicio()
{
    pantallaMenu->checkSaveSlots();
    pantallaMenu->continueMusic();
    pantallas->setCurrentWidget(pantallaMenu);
    pantallaMenu->setInicio();
}

/// ################################## PANTALLA DE PAUSA #############################################
void MainWindow::PrepararPantallaPausa()
{
    if (pantallas->currentWidget() != pantallaTutorial)
        PantallaPrevia = pantallas->currentIndex(); // Guardamos la pantalla previa

    if (pantallas->currentWidget() == gameScreen)
        gameScreen->PausarJuego();

    transicion->ArrancarTransicion(500, this, &MainWindow::PonerPantallaPausa);
}

void MainWindow::PrepararSalirPantallaPausa()
{
    transicion->ArrancarTransicion(500, this, &MainWindow::VolverPantallaAnterior);
}

void MainWindow::PonerPantallaPausa()
{
    if (PantallaPrevia == 0 || PantallaPrevia == 3 || PantallaPrevia == 4){
        pantallaMenu->stopMusic();
        pantallaPausa->BlockVolverMenu(true);
    } else pantallaPausa->BlockVolverMenu(false);

    pantallas->setCurrentWidget(pantallaPausa);
    pantallaPausa->setInicio();
}

void MainWindow::VolverPantallaAnterior()
{
   pantallas->setCurrentIndex(PantallaPrevia);
    if (pantallas->currentWidget() == pantallaMenu)
       pantallaMenu->continueMusic();

    if (pantallas->currentWidget() == gameScreen)
        gameScreen->ReanudarJuego();
}

void MainWindow::PonerModoVentana()
{
    this->showNormal();  // Cambia a modo ventana normal
    this->resize(1280, 720);  // Establece la ventana en 720p
    this->CalcularCentroDePantalla();
    this->move(this->CentroPantallaX, this->CentroPantallaY);
}

void MainWindow::CalcularCentroDePantalla()
{
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    this->CentroPantallaX = (screenGeometry.width() - this->width()) / 2;
    this->CentroPantallaY = (screenGeometry.height() - this->height()) / 2;
}

/// ####################### PANTALLA TUTORIAL ########################
void MainWindow::PrepararTutorial()
{
    PantallaPreviaTutorial = pantallas->currentIndex();
    pantallaTutorial->iniciar();
    transicion->ArrancarTransicion(1000, this, &MainWindow::SetTutorial);
}

void MainWindow::PrepararSalirTutorial()
{
    transicion->ArrancarTransicion(1000, this, &MainWindow::SalirTutorial);
}

void MainWindow::SetTutorial()
{
    pantallaMenu->stopMusic();
    pantallas->setCurrentWidget(pantallaTutorial);
}

void MainWindow::SalirTutorial()
{
    pantallas->setCurrentIndex(PantallaPreviaTutorial);
}


// ###################################### LOGS ###################################
void MainWindow::ConexionesLogs()
{
    connect(pantallaPausa, &PantallaPausa::EnviarLogs, &log, &Logs::RecibirLogs);
    connect(pantallaFinalNivel,&PantallaFinalNivel::EnviarLogs,&log,&Logs::RecibirLogs);
    connect(pantallaMenu,&PantallaMenu::EnviarLogs,&log, &Logs::RecibirLogs);
    connect(gameScreen,&GameScreen::EnviarLogs,&log,&Logs::RecibirLogs);
    connect(juego,&Juego::Log,&log,&Logs::RecibirLogs);
    connect(&guardarPartida, &GuardarPartidas::Log, &log, &Logs::RecibirLogs);
}
