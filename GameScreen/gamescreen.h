#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QWidget>
#include <QResizeEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QSpacerItem>

#include "../NPC/npcgenericoui.h"
#include "../Documentos/uaderpass.h"
#include "../Gestores/gestornpcsui.h"
#include "../juego.h"
#include "BotonesCustom.h"
#include "pantallaperdiste.h"
#include "../Documentos/docsiconui.h"

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
    void PrepararJuego(int Nivel = 1, int Dificultad = 2);
    /// PrepararJuego(int Nivel, int Dificultad, PlayerStats) A futuro para cuando tengamos partidas guardadas
    void Restart();
    void Centrar();

public slots:
    void PausarJuego();
    void ReanudarJuego();
    void BloquearBotones(bool Bloqueo);
    void DesbloquearBotones();

signals:
    void NivelTerminado(bool Perdio);

private slots:
    void FinalDePartida();
    void Decidir();

private:
    Ui::GameScreen *ui;
    PantallaPerdiste* pantallaPerdiste;
    Juego* juego;
    QTimer tiempoPartida;
    QTimer temporizadorBotones;
    int tiempoRestante;

    GestorNPCsUI GestorNPC;

    BotonesCustom* BotonAprobar;
    BotonesCustom* BotonRechazar;
    BotonesCustom* BotonCentrar;
    QSpacerItem* EspaciadorBotones;

    // Botones
    void SpawnearBotones();
    void RealizarConexiones();
    void RealizarConexionesPrincipales();

    // no se como hacer esto asi q lo voy a hacer asi nomas
    void Acepto();
    void Rechazo();
    void SelloDocumento(bool Boton);

    // Reubicar NPCs en la escena
    void changeEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
};

#endif // GAMESCREEN_H
