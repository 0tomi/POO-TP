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
#include "libroreglas.h"
#include "../Gestores/gestordocumentosui.h"
#include "../Documentos/transcriptordialogos.h"
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

public slots:
    void PausarJuego();
    void ReanudarJuego();
    void FinalDePartida();

signals:
    void NivelTerminado(bool Perdio);

protected:
    void keyPressEvent(QKeyEvent *event) override; // Para detectar cuando se presiona una tecla

private slots:
    void Decidir();

private:
    Ui::GameScreen *ui;
    PantallaPerdiste* pantallaPerdiste;
    Juego* juego;
    QTimer tiempoPartida;
    int tiempoRestante;

    bool Pausado;

    // Documentos que deja el NPC
    DocsIconUI * IconoDocs;
    void setUpIconoDocsUI();

    // Gestores
    GestorNPCsUI GestorNPC;
    GestorDocumentosUI GestorDocs;

    void SetearConexionesDocumentos();

    BotonesCustom* BotonAprobar;
    BotonesCustom* BotonRechazar;
    BotonesCustom* BotonCentrar;
    QSpacerItem* EspaciadorBotones;

    // Controlar tiempo en partida
    QTimer TiempoDia;
    void ActualizarTiempo();
    int TiempoActual;

    // Botones
    void SpawnearBotones();
    void RealizarConexionesPrincipales();
    void BloquearBotones(bool Bloqueo);
    void DesbloquearBotones();
    bool BotonesBloqueados = false;

    // no se como hacer esto asi q lo voy a hacer asi nomas
    void Acepto();
    void Rechazo();
    void SelloDocumento(bool Boton);

    // Reubicar NPCs en la escena
    void changeEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    // Aparecer libro de reglas
    void setUpLibroReglas();
    libroreglas * libroReglasUI;
    QTimer bloquearBotonReglas;
    bool MostrandoReglas;
    void MostrarReglas();
};

#endif // GAMESCREEN_H
