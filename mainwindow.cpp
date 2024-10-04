#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

/// ############################### CONSTRUCTOR #######################################
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/Resources/th.jpeg"));
    setWindowTitle("Trabajo practico de POO");

    CrearPantallasJuego();

    ConeccionesPantallaPausa();
    ConeccionesPantallaMenu();
    ConeccionesPantallaEstadisticas();
    ConeccionesLogs();
    // Mostrar en pantalla completa:
    this->showFullScreen();
    pantallaPausa->setWindowedButton();

    // Hacemos que al cambiar de pantalla, la pantalla que se muestre sea el nuevo foco.
    pantallaMenu->setFocus();
    connect(pantallas, &QStackedWidget::currentChanged, [this](){
        QWidget * pantallaActual = pantallas->currentWidget();
        pantallaActual->setFocus(); // polimorfismo locura
    });

    /// ##################### TEST ################################
    connect(gameScreen, &GameScreen::EnviarLogs, [this](QString dato){
        qDebug() << dato;
    });
    connect(juego, &Juego::Log, [this](QString dato){
        qDebug() << dato;
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

    pantallaMenu = new PantallaMenu(&guardarPartida, this);
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
void MainWindow::ConeccionesPantallaPausa()
{
    // Conectamos las señales del menu de pausa
    connect(pantallaPausa, &PantallaPausa::setFullScreen, this, &MainWindow::showFullScreen);
    connect(pantallaPausa, &PantallaPausa::setWindowedScreen, this, &MainWindow::PonerModoVentana);
    connect(pantallaPausa, &PantallaPausa::return2lastWidget, this, &MainWindow::PrepararSalirPantallaPausa);
    connect(pantallaPausa, &PantallaPausa::quit, this, &MainWindow::VolverInicio);
    connect(pantallaPausa, &PantallaPausa::clickedTutorial, this, &MainWindow::PrepararTutorial);
    connect(pantallaPausa, &PantallaPausa::soundVolume, gameScreen , &GameScreen::setVolumenes);
    connect(pantallaPausa, &PantallaPausa::soundVolume, pantallaMenu , &PantallaMenu::setVolumen);
    connect(pantallaPausa, &PantallaPausa::musicVolume, pantallaMenu, &PantallaMenu::setMusicVolume);
}

void MainWindow::ConeccionesPantallaMenu()
{
    // Cuando se clickee jugar, abrimos el juego:
    connect(pantallaMenu, &PantallaMenu::clickedStartDefault, [this](int dif){this->TransicionJuego(1,dif);});
    connect(pantallaMenu, &PantallaMenu::clickedStart, this, &MainWindow::TransicionJuego);
    connect(pantallaMenu, &PantallaMenu::clickedSettings, this, &MainWindow::PrepararPantallaPausa);
    connect(pantallaMenu, &PantallaMenu::clickedSalir, this, &MainWindow::close);
    connect(pantallaMenu, &PantallaMenu::clickedTutorial, this, &MainWindow::PrepararTutorial);
}

void MainWindow::ConeccionesPantallaEstadisticas()
{
    connect(pantallaFinalNivel, &PantallaFinalNivel::salirClicked, this, &MainWindow::VolverInicio);
    connect(pantallaFinalNivel, &PantallaFinalNivel::sigNivelClicked, this, &MainWindow::TransicionJuego);
    connect(pantallaFinalNivel, &PantallaFinalNivel::reintentarClicked, this, &MainWindow::TransicionJuego);

    // Conectamos el final de la partida con el nivel terminado
    connect(gameScreen, &GameScreen::NivelTerminado, this, &MainWindow::PrepararPantallaFinalNivel);
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
        QApplication::quit();  // Cerrar la aplicación
    } else {
        event->ignore();  // Ignorar el evento y no cerrar la ventana
    }
}

/// ################################## PANTALLA DE JUEGO #############################################

void MainWindow::TransicionJuego(int Nivel, int Dificultad)
{
    pantallaMenu->stopMusic();
    transicion->ArrancarTransicion(1000, this, &MainWindow::PrepararJuego);

    // A futuro cambiar por los inputos de los botones.
    gameScreen->PrepararJuego(Nivel, Dificultad);

    // Conectamos el final de la animacion, para mostrar la ventana del juego.
    connect(transicion, &PantallaTransicion::terminoAnimacion, this, &MainWindow::IniciarJuego);
}

void MainWindow::PrepararJuego()
{
    pantallas->setCurrentWidget(gameScreen);    // Colocamos la pantalla de juego, aunque esto suceda a la mitad de animacion, por lo tanto no se ve.
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
void MainWindow::ConeccionesLogs()
{
    connect(pantallaPausa, &PantallaPausa::EnviarLogs, &log, &Logs::RecibirLogs);
    connect(pantallaFinalNivel,&PantallaFinalNivel::EnviarLogs,&log,&Logs::RecibirLogs);
    connect(pantallaMenu,&PantallaMenu::EnviarLogs,&log, &Logs::RecibirLogs);
    connect(gameScreen,&GameScreen::EnviarLogs,&log,&Logs::RecibirLogs);
    connect(juego,&Juego::Log,&log,&Logs::RecibirLogs);
}
