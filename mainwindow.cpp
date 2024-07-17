#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Juego locura POO");

    CrearPantallasJuego();

    // Mostrar en pantalla completa:
    this->showFullScreen();
    pantallaPausa->setWindowedButton();

    // Conectamos las señales del menu de pausa
    connect(pantallaPausa, &PantallaPausa::setFullScreen, this, &MainWindow::showFullScreen);
    connect(pantallaPausa, &PantallaPausa::setWindowedScreen, this, &MainWindow::PonerModoVentana);
    connect(pantallaPausa, &PantallaPausa::return2lastWidget, this, &MainWindow::PrepararSalirPantallaPausa);
    connect(pantallaPausa, &PantallaPausa::quit, this, &MainWindow::closeEvent);

    // Cuando se clickee jugar, abrimos el juego:
    connect(pantallaInicio, &PantallaInicio::ClickeoBotonEmpezar, this, &MainWindow::TransicionJuego);

    // Cuando termine un nivel, hacemos que se muestre la pantalla de final de nivel
    connect(gameScreen, &GameScreen::NivelTerminado, this, &MainWindow::PrepararPantallaFinalNivel);

    // Conectamos la pantalla de estadisticas con lo demas
    connect(pantallaFinalNivel, &PantallaFinalNivel::sigNivelClicked, this, &MainWindow::VolverInicio);
    connect(pantallaFinalNivel, &PantallaFinalNivel::salirClicked, this, &MainWindow::VolverInicio);
    connect(pantallaFinalNivel, &PantallaFinalNivel::reintentarClicked, this, &MainWindow::TransicionJuego);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete juego;
    delete pantallaInicio;
    delete pantallaPausa;
    delete pantallaTransicion;
    delete pantallaFinalNivel;
    delete gameScreen;
    delete pantallas;
    // aca iria el delete a las pantallas
}

void MainWindow::PrepararPantallaFinalNivel(bool Perdio)
{
    ArrancarTransicion(1000);
    pantallaFinalNivel->setPantallaFinalUI(juego, Perdio);

    // Si perdio, reseteamos las estadisticas para que pueda volver a jugar
    if (Perdio)
        gameScreen->Restart();

    connect(iniciarTransicion, &QAbstractAnimation::finished, this, &MainWindow::setPantallaStats);
}

void MainWindow::setPantallaStats()
{
    pantallas->setCurrentWidget(pantallaFinalNivel);
    connect(iniciarTransicion, &QAbstractAnimation::finished, this, &MainWindow::setPantallaStats);
}

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

void MainWindow::TransicionJuego()
{
    ArrancarTransicion(1000);

    // A futuro cambiar por los inputos de los botones.
    gameScreen->PrepararJuego();

    // Conectamos el final de la primer animacion, con la preparacion del juego
    connect(iniciarTransicion, &QPropertyAnimation::finished, this, &MainWindow::PrepararJuego);

    // Conectamos el final de la animacion, para mostrar la ventana del juego.
    connect(terminarTransicion, &QPropertyAnimation::finished, this, &MainWindow::IniciarJuego);
}

void MainWindow::PrepararJuego()
{
    // Desconectamos la animacion para poder usar despues la pantalla de transicion
    disconnect(iniciarTransicion, &QPropertyAnimation::finished, this, &MainWindow::PrepararJuego);
    pantallas->setCurrentWidget(gameScreen);    // Colocamos la pantalla de juego, aunque esto suceda a la mitad de animacion, por lo tanto no se ve.
}

void MainWindow::IniciarJuego()
{
    // Desconectamos la animacion para poder usar despues la pantalla de transicion
    disconnect(terminarTransicion, &QPropertyAnimation::finished, this, &MainWindow::IniciarJuego);
    gameScreen->EmpezarJuego(); // Aca dsps iria el nivel de juego que toca.
}

void MainWindow::CrearPantallasJuego()
{
    // Iniciamos la logica del juego
    juego = new Juego();

    // Seteamos el widget donde se acomodaran las distintas pantallas del juego
    pantallas = new QStackedWidget(this);
    setCentralWidget(pantallas);

    // Creamos las pantallas del juego
    pantallaInicio = new PantallaInicio(this);
    gameScreen = new GameScreen(juego, this);
    pantallaPausa = new PantallaPausa(this);
    pantallaFinalNivel = new PantallaFinalNivel(this);
    CrearPantallaTransicion();

    // Añadimos las pantallas al stack
    pantallas->addWidget(pantallaInicio);
    pantallas->addWidget(gameScreen);
    pantallas->addWidget(pantallaPausa);
    pantallas->addWidget(pantallaFinalNivel);

    // Mostramos la pantalla de inicio
    setInicio();
}

void MainWindow::CrearPantallaTransicion()
{
    // Armo pantalla para las transiciones
    pantallaTransicion = new QWidget(this);
    pantallaTransicion->setStyleSheet("background-color: black;");
    pantallaTransicion->hide();
    pantallaTransicion->setFixedSize(1920,1080);

    // Damos opacidad 0 para que aparezca la pantalla y no se vea
    this->efecto = new QGraphicsOpacityEffect(pantallaTransicion);
    efecto->setOpacity(0);
    pantallaTransicion->setGraphicsEffect(efecto);

    // Animacion para que aparezca el fondo
    this->iniciarTransicion = new QPropertyAnimation(efecto, "opacity");
    iniciarTransicion->setStartValue(0.0); // opacidad inicial (completamente invisible)
    iniciarTransicion->setEndValue(1.0); // opacidad final (completamente visible)

    // Animacion para que desaparezca el fondo
    this->terminarTransicion = new QPropertyAnimation(efecto, "opacity");
    terminarTransicion->setStartValue(1.0); // opacidad inicial (completamente visible)
    terminarTransicion->setEndValue(0.0); // opacidad final (completamente invisible)

    // Conectamos el final de la animacion de inicio, con la de la animacion de final.
    connect(iniciarTransicion, &QAbstractAnimation::finished, this, &MainWindow::MidTransicion);
    connect(terminarTransicion, &QAbstractAnimation::finished, this, &MainWindow::TerminarTransicion);
}

void MainWindow::PonerModoVentana()
{
    this->showNormal();  // Cambia a modo ventana normal
    this->resize(1280, 720);  // Establece la ventana en 720p
    this->CalcularCentroDePantalla();
    this->move(this->CentroPantallaX, this->CentroPantallaY);
}

void MainWindow::VolverInicio()
{
    ArrancarTransicion(1000);
    connect(iniciarTransicion, &QAbstractAnimation::finished, this, &MainWindow::setInicio);
}

void MainWindow::setInicio()
{
    pantallas->setCurrentWidget(pantallaInicio);
}

void MainWindow::PrepararPantallaPausa()
{
    ArrancarTransicion(500);
    if (pantallas->currentWidget() == gameScreen)
        gameScreen->PausarJuego();

    // Cuando este a mitad de animacion colocamos la pantalla de pausa
    connect(iniciarTransicion, &QAbstractAnimation::finished, this, &MainWindow::PonerPantallaPausa);
}

void MainWindow::PrepararSalirPantallaPausa()
{
    ArrancarTransicion(500);
    connect(iniciarTransicion, &QAbstractAnimation::finished, this, &MainWindow::VolverPantallaAnterior);

    if (pantallas->currentWidget() == gameScreen)
        gameScreen->ReanudarJuego();
}

void MainWindow::PonerPantallaPausa()
{
    // Desconectamos la pantalla para poder usarla en otras cosas luego
    disconnect(iniciarTransicion, &QAbstractAnimation::finished, this, &MainWindow::PonerPantallaPausa);

    PantallaPrevia = pantallas->currentIndex(); // Guardamos la pantalla previa
    pantallas->setCurrentWidget(pantallaPausa);
}

void MainWindow::VolverPantallaAnterior()
{
    // Desconectamos la pantalla para poder usarla en otras cosas luego
    disconnect(iniciarTransicion, &QAbstractAnimation::finished, this, &MainWindow::VolverPantallaAnterior);
    pantallas->setCurrentIndex(PantallaPrevia);
}

void MainWindow::ArrancarTransicion(int Duracion)
{
    iniciarTransicion->setDuration(Duracion); // duración en milisegundos
    terminarTransicion->setDuration(Duracion);

    // Colocamos la opacidad en 0 para arrancar la animacion
    efecto->setOpacity(0);

    pantallaTransicion->show();
    iniciarTransicion->start();
}

void MainWindow::MidTransicion()
{
    terminarTransicion->start();
}

void MainWindow::TerminarTransicion()
{
    pantallaTransicion->hide();
}

void MainWindow::CalcularCentroDePantalla()
{
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    this->CentroPantallaX = (screenGeometry.width() - this->width()) / 2;
    this->CentroPantallaY = (screenGeometry.height() - this->height()) / 2;
}
