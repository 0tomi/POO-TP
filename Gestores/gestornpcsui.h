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
    void setUpPartidaEmpezada(int cantidad_NPCs_pasados);
    void setUp(QWidget * EscenarioTranscriptor, QWidget *EscenarioNPCs, ColaNPC* cola);
    void setUpTranscriptor(QPushButton *boton);

    void EmpezarJuego();
    void Centrar();

    void setVolumen(float);

    void Entrar();
    NPC* getNPC();
    void Salir(bool Boton);

    void TerminoNivel();
    bool MostrandoElNPC() const;

    int NPCsRestantes();

    bool getValidez();
    int getTipo();
    QString getDatosFalsos();

    void Pausar();
    void Reanudar();

    void SalirForzado();
    int getCantidad_NPCs_pasados() const;

public slots:
    void SalirEntidades();

signals:
    void logs(QString);
    void setDocsInfo(NPC * info);
    void NPCCambiado();
    void ColaTerminada();
    void UltimoNPC();

    void NPCHablo();
    void NPCContesto();

    void NPCEntro();
    void NPCSalio();

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
    bool ColaVacia;

    int topeNPCs;
    int cantidad_NPCs_pasados;
    int NivelActual;
    void RealizarConexionesDeNPCs();
    void DesconectarNPCs();
    bool NPCConectado;
    void ActualizarEstadoNPC();
    void FinalizarEntidades();
    void GenerarLog (NPC* info);
};

#endif // GESTORNPCSUI_H
