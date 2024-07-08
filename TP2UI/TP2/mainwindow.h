#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pantallainicio.h"
#include "gamescreen.h"
#include "juego.h"

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
    void TransicionJuego();
    void PrepararJuego();
    void IniciarJuego();


private:
    Ui::MainWindow *ui;

    // Juego
    Juego* juego;

    // Pantallas del juego:
    void CrearPantallasJuego();
    void CrearPantallaTransicion();

    QStackedWidget *pantallas;
    PantallaInicio *pantallaInicio;
    GameScreen *gameScreen;
    QWidget* pantallaTransicion;

    QPropertyAnimation* iniciarTransicion;
    QPropertyAnimation* terminarTransicion;
    QGraphicsOpacityEffect* efecto;


    // Calcular el centro de la pantalla
    void CalcularCentroDePantalla();
    int CentroPantallaX;
    int CentroPantallaY;
};
#endif // MAINWINDOW_H
