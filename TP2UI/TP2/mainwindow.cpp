#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Seteamos el widget donde se acomodaran las distintas pantallas del juego
    pantallas = new QStackedWidget(this);
    setCentralWidget(pantallas);

    // Creamos las pantallas del juego
    pantallaInicio = new PantallaInicio(this);
    gameScreen = new GameScreen(this);

    // Armo pantalla para las transiciones
    pantallaTransicion = new QWidget(this);
    pantallaTransicion->setStyleSheet("background-color: black;");

    // Añadimos las pantallas al stack
    pantallas->addWidget(pantallaInicio);
    pantallas->addWidget(gameScreen);
    pantallas->addWidget(pantallaTransicion);

    // Mostramos la pantalla de inicio
    pantallas->setCurrentWidget(pantallaInicio);

    // Mostrar en pantalla completa:
    this->showFullScreen();

    // Cuando se clickee jugar, abrimos el juego:
    connect(pantallaInicio, &PantallaInicio::ClickeoBotonEmpezar, this, &MainWindow::TransicionJuego);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        if (this->isFullScreen()) {
            this->showNormal();  // Cambia a modo ventana normal
            this->resize(1280, 720);  // Establece la ventana en 720p

            this->CalcularCentroDePantalla();
            this->move(this->CentroPantallaX, this->CentroPantallaY);
        } else {
            // Cambia a modo pantalla completa si no lo está
            this->move(this->CentroPantallaX, this->CentroPantallaY);
            this->showFullScreen();
        }
    }
    QMainWindow::keyPressEvent(event);  // Llama al método base para manejar otros eventos de teclado
}

void MainWindow::TransicionJuego()
{
    // ## FALTARIA ACA UNA ANIMACION DONDE LA PANTALLA SE PONE EN NEGRO Y ARRANCA EL JUEGO ##
    this->efecto = new QGraphicsOpacityEffect(pantallaTransicion);
    efecto->setOpacity(0.2);
    pantallaTransicion->setGraphicsEffect(efecto);

    // Animacion para que aparezca el fondo
    this->iniciarTransicion = new QPropertyAnimation(efecto, "opacity");
    iniciarTransicion->setDuration(1000); // duración en milisegundos
    iniciarTransicion->setStartValue(0.0); // opacidad inicial (completamente invisible)
    iniciarTransicion->setEndValue(1.0); // opacidad final (completamente visible)

    // Animacion para que desaparezca el fondo
    this->terminarTransicion = new QPropertyAnimation(efecto, "opacity");
    terminarTransicion->setDuration(1000); // duración en milisegundos
    terminarTransicion->setStartValue(1.0); // opacidad inicial (completamente visible)
    terminarTransicion->setEndValue(0.0); // opacidad final (completamente invisible)

    // Conectamos el final de la primer animacion, al iniciode la 2da, usando un lambda porque sino no deja.
    connect(iniciarTransicion, &QPropertyAnimation::finished, [=]() {terminarTransicion->start();});
    // Conectamos el final de la animacion, para mostrar la ventana del juego.
    connect(terminarTransicion, &QPropertyAnimation::finished, this, &MainWindow::IniciarJuego);

    pantallas->setCurrentWidget(pantallaTransicion);
    iniciarTransicion->start();

    /*
        La forma ideal de hacer esto, seria
        insertar pantallaTransicion como una pantalla por arriba,
        pero lo vamos a dejar para dsps.
    */
}

void MainWindow::IniciarJuego()
{
    connect(pantallas, &QStackedWidget::currentChanged, gameScreen, &GameScreen::EmpezarJuego);

    pantallas->setCurrentWidget(gameScreen);

    // Borramos las animaciones y el efecto
    delete iniciarTransicion;
    delete terminarTransicion;

    efecto->setOpacity(1.0);
    pantallaTransicion->setGraphicsEffect(efecto);
    delete efecto;
}


void MainWindow::CalcularCentroDePantalla()
{
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    this->CentroPantallaX = (screenGeometry.width() - this->width()) / 2;
    this->CentroPantallaY = (screenGeometry.height() - this->height()) / 2;
}
