#ifndef GESTORNPCSUI_H
#define GESTORNPCSUI_H

#include <QWidget>
#include <QTimer>
#include <QPushButton>

#include "../NPC/npcgenericoui.h"
#include "../NPC/npccomun.h"
#include "../NPC/globosdialogoui.h"
#include "../Generadores/colanpc.h"
#include "../Documentos/transcriptordialogos.h"

class GestorNPCsUI: public QWidget
{
    Q_OBJECT

public:
    GestorNPCsUI();
    ~GestorNPCsUI();
    void setUp(QWidget * EscenarioTranscriptor, QWidget *EscenarioNPCs, ColaNPC* cola);
    void setUpTranscriptor(QPushButton *boton);

    void EmpezarJuego();
    void Centrar();

    void Entrar();
    void Salir(bool Boton);

    void TerminoNivel();
    bool MostrandoElNPC() const;

    int NPCsRestantes();

    bool getValidez();
    int getTipo();

    void Pausar();
    void Reanudar();

public slots:
    void SalirEntidades();

signals:
    void setDocsInfo(NPC * info);
    void NPCCambiado();
    void ColaTerminada();
    void UltimoNPC();

    void NPCHablo();
    void NPCContesto();

    void NPCEntro();
    void NPCSalio();

    void NPCTerminoEntrar();
    void NPCTerminoSalir();

private slots:
    void emitirNPCTerminoSalir();
    void emitColaTerminada();

private:
    ColaNPC* ColaNPCs;
    QWidget* Escenario;
    TranscriptorDialogos * transcriptorDialogos;

    // NPCs
    NPCGenericoUI* NPCcomunUI;
    NPC* NPCenEscena;
    bool Rechazado;

    GlobosDialogoUI* Dialogos;

    bool MostrandoNPC;

    int topeNPCs;
    int NivelActual;
    void RealizarConexionesDeNPCs();
    void DesconectarNPCs();
    bool NPCConectado;
    void ActualizarEstadoNPC();
};

#endif // GESTORNPCSUI_H
