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

    // Añadimos las pantallas al stack
    pantallas->addWidget(pantallaInicio);
    pantallas->addWidget(gameScreen);

    // Mostramos la pantalla de inicio
    pantallas->setCurrentWidget(pantallaInicio);

    // Mostrar en pantalla completa:
    this->showFullScreen();

    // Cuando se clickee jugar, abrimos el juego:
    connect(pantallaInicio, &PantallaInicio::ClickeoBotonEmpezar, this, &MainWindow::IniciarJuego);
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

void MainWindow::IniciarJuego()
{
    pantallas->setCurrentWidget(gameScreen);
}

void MainWindow::CalcularCentroDePantalla()
{
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    this->CentroPantallaX = (screenGeometry.width() - this->width()) / 2;
    this->CentroPantallaY = (screenGeometry.height() - this->height()) / 2;
}
