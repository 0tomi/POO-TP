#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pantallainicio.h"
#include "gamescreen.h"

#include <QMainWindow>
#include <QStackedWidget>
#include <QKeyEvent>

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

private:
    Ui::MainWindow *ui;

    // Pantallas del juego:
    QStackedWidget *pantallas;
    PantallaInicio *pantallaInicio;
    GameScreen *gameScreen;
    void IniciarJuego();

    // Calcular el centro de la pantalla
    void CalcularCentroDePantalla();
    int CentroPantallaX;
    int CentroPantallaY;
};
#endif // MAINWINDOW_H
