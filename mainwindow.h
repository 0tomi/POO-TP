#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GameScreen/gamescreen.h"
#include "PantallaStats/pantallafinalnivel.h"
#include "PantallaMenu/pantallamenu.h"
#include "juego.h"
#include "PantallaPausa/pantallapausa.h"
#include "PantallaTransicion/pantallatransicion.h"
#include "GameScreen/pantallatutorial.h"
#include "logs.h"

#include <QMainWindow>
#include <QStackedWidget>
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override; // Para detectar cuando se presiona una tecla
    void closeEvent(QCloseEvent *event) override;

private slots:
    void TransicionJuego(int Nivel = 1, int Dificultad = 2);
    void PrepararJuego();
    void IniciarJuego();
    void PrepararPantallaFinalNivel(bool Perdio);

private:
    Ui::MainWindow *ui;

    // Juego
    Juego* juego;

    // Pantallas del juego:
    void CrearPantallasJuego();
    void CrearPantallaTransicion();
    void PonerModoVentana();

    void VolverInicio();
    void setInicio();
    void setPantallaStats();

    QStackedWidget *pantallas;
    int PantallaPrevia;
    GameScreen *gameScreen;

    // Pantalla de estadisticas
    PantallaFinalNivel *pantallaFinalNivel;
    void ConeccionesPantallaEstadisticas();

    // Pantalla de menu
    PantallaMenu * pantallaMenu;
    void ConeccionesPantallaMenu();

    // Pantalla de pausa
    PantallaPausa * pantallaPausa;
    void PrepararPantallaPausa();
    void PrepararSalirPantallaPausa();
    void PonerPantallaPausa();
    void VolverPantallaAnterior();
    void ConeccionesPantallaPausa();

    // Transicion
    PantallaTransicion * transicion;

    // Tutorial
    PantallaTutorial * pantallaTutorial;
    int PantallaPreviaTutorial;
    void PrepararTutorial();
    void PrepararSalirTutorial();
    void SetTutorial();
    void SalirTutorial();

    // Logs
    Logs log;
    void ConeccionesLogs();

    // Calcular el centro de la pantalla
    void CalcularCentroDePantalla();
    int CentroPantallaX;
    int CentroPantallaY;
};
#endif // MAINWINDOW_H
