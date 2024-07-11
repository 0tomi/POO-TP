#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QWidget>
#include <QResizeEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QSpacerItem>

#include "NPC/npcgenericoui.h"
#include "Documentos/uaderpass.h"
#include "Documentos/gestordocumentosui.h"
#include "juego.h"
#include "GameScreen/tomibotones.h"

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
    void PrepararJuego(int Nivel);

private slots:
    void FinalDePartida();

private:
    Ui::GameScreen *ui;
    Juego* juego;
    ColaNPC* Cola;
    QTimer tiempoPartida;
    QTimer temporizadorBotones;

    GestorDocumentosUI documentos;

    TomiBotones* BotonAprobar;
    TomiBotones* BotonRechazar;
    TomiBotones* BotonCentrar;
    QSpacerItem* EspaciadorBotones;

    void SpawnearBotones();
    void RealizarConecciones();
    void RealizarConeccionesPrincipales();

    // no se como hacer esto asi q lo voy a hacer asi nomas
    void Acepto();
    void Rechazo();
    void SelloDocumento(bool Boton);
    void BloquearBotones(bool Bloqueo);
    void FuncionBotonCentral();
    // Otro metodo que voy  a poner simplemente porque no se como se hace.
    void DesbloquearBotones();

    // Documentos
    DocumentosUI* doc;

    void CentrarDocumentos();
    void EntrarDOC();
    void SacarDOC();

    // NPCs
    NPCGenericoUI *npcUI;
    NPC *NPCenEscena;

    void SpawnearNPC();
    void EntrarNPC();
    void SacarNPC();
    void CentrarNPC();

    // Reubicar NPCs en la escena
    void changeEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
};

#endif // GAMESCREEN_H
