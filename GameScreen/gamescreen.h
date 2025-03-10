#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QWidget>
#include <QResizeEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QSpacerItem>

#include "../SaveSlots/PlayerStats.h"
#include "../Gestores/gestornpcsui.h"
#include "../juego.h"
#include "BotonesCustom.h"
#include "pantallaperdiste.h"
#include "../Documentos/docsiconui.h"
#include "libroreglas.h"
#include "../Gestores/gestordocumentosui.h"
#include "../Documentos/docsiconui.h"
#include "intropantalla.h"
#include "notificacion.h"
#include "../Documentos/radiografiaui.h"
#include "../Gestores/gestorfondonpcs.h"


namespace Ui {
class GameScreen;
}

class GameScreen : public QWidget
{
    Q_OBJECT

public:
    explicit GameScreen(Juego* newJuego, QWidget *parent = nullptr);
    ~GameScreen();

    void Iniciar();
    void PrepararJuego(int Nivel = 1, int Dificultad = 2);
    void PrepararJuegoCheat(int LvL, int Dificultad, quint32 seed);
    void PrepararJuego(PlayerStats);

    /// PrepararJuego(int Nivel, int Dificultad, PlayerStats) A futuro para cuando tengamos partidas guardadas
    void Restart();

public slots:
    void PausarJuego();
    void ReanudarJuego();
    void FinalDePartida();
    void setVolumenes(float);
    void setMusicVolume(float vol);

signals:
    void NivelTerminado(bool Perdio);
    void EnviarLogs(QString);
    void Guardar(PlayerStats&);

protected:
    void keyPressEvent(QKeyEvent *event) override; // Para detectar cuando se presiona una tecla

private slots:
    void Decidir();

private:
    PlayerStats playerStats;
    int dificultad;
    Ui::GameScreen *ui;
    PantallaPerdiste* pantallaPerdiste;
    Juego* juego;
    int nivelActual;
    QTimer tiempoPartida;
    int tiempo;
    int tiempoRestante;

    bool Pausado;
    bool DecisionJugador;
    bool gameHasBeenFinished;

    // Sonidos
    QRandomGenerator random;
    QSoundEffect Musica[6];
    int currentMusic;
    void setUpSonidos();

    // Documentos que deja el NPC
    DocsIconUI * IconoDocs;
    void setUpIconoDocsUI();

    // Gestores
    GestorNPCsUI GestorNPC;
    GestorDocumentosUI GestorDocs;
    GestorFondoNPCs GestorFondo;

    void SetearConexionesDocumentos();

    BotonesCustom* BotonAprobar;
    BotonesCustom* BotonRechazar;
    BotonesCustom* BotonCentrar;
    BotonesCustom * BotonScanner;
    QSpacerItem* EspaciadorBotones;

    // Controlar tiempo en partida
    QTimer TiempoDia;
    int cantidadTiempoDia;
    void ActualizarTiempo();
    void arrancarJuego();
    int TiempoActual;

    // Botones
    void SpawnearBotones();
    void RealizarConexionesPrincipales();
    void BloquearBotones(bool Bloqueo);
    void DesbloquearBotones();
    bool BotonesBloqueados = false;
    void setUpBotonEscanner();

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

    // Intro del juego
    IntroPantalla* introPantalla;

    // Notificaciones
    float volumenActual;
    vector<Notificacion*> Notificaciones;
    int CantidadNotificaciones = 0;
    void CrearNotificacion(bool Multa, QString& Motivo);
    void MatarNotificaciones();
    void MatarNotificacion(int Numero);

    // Radiografia
    radiografiaui * RadiografiaUI;

    // Modo demonio
    QTimer tiempoNPC;
    const int tiempoPorNPC = 45 * 1000;
    int remainingTiempoNPC;
    bool ModoDemonActivo;
};

#endif // GAMESCREEN_H
