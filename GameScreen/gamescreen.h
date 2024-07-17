#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QWidget>
#include <QResizeEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QSpacerItem>
#include <QPushButton>
#include <QPixmap>

#include "../NPC/npcgenericoui.h"
#include "../Documentos/uaderpass.h"
#include "../Gestores/gestornpcsui.h"
#include "../juego.h"
#include "BotonesCustom.h"


namespace Ui {
class GameScreen;
}

class GameScreen : public QWidget
{
    Q_OBJECT

public:
    explicit GameScreen(Juego* newJuego, QWidget *parent = nullptr);
    ~GameScreen();
    void EmpezarJuego();
    void PrepararJuego(bool Reset = false, int Nivel = 1, int Dificultad = 2);

public slots:
    void PausarJuego();
    void ReanudarJuego();

signals:
    void NivelTerminado();
    void JuegoFallado();

private slots:
    void FinalDePartida();


private:
    Ui::GameScreen *ui;
    Juego* juego;
    QTimer tiempoPartida;
    QTimer temporizadorBotones;
    int tiempoRestante;

    GestorNPCsUI GestorNPC;

    BotonesCustom* BotonAprobar;
    BotonesCustom* BotonRechazar;
    BotonesCustom* BotonCentrar;
    QSpacerItem* EspaciadorBotones;

    void SpawnearBotones();
    void RealizarConecciones();
    void RealizarConeccionesPrincipales();
    void Spawnear_libro();

    // no se como hacer esto asi q lo voy a hacer asi nomas
    void Acepto();
    void Rechazo();
    void SelloDocumento(bool Boton);
    void BloquearBotones(bool Bloqueo);
    // Otro metodo que voy  a poner simplemente porque no se como se hace.
    void DesbloquearBotones();

    // Reubicar NPCs en la escena
    void changeEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
};

#endif // GAMESCREEN_H
