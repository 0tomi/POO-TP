#ifndef GESTORNPCSUI_H
#define GESTORNPCSUI_H

#include <QWidget>
#include <QTimer>
#include <QPushButton>

#include "../NPC/npcgenericoui.h"
#include "../NPC/npccomun.h"
#include "../NPC/globosdialogoui.h"
#include "../Generadores/colanpc.h"
#include "gestordocumentosui.h"
#include "../Documentos/docsiconui.h"
#include "../Documentos/transcriptordialogos.h"

class GestorNPCsUI: public QWidget
{
    Q_OBJECT

public:
    GestorNPCsUI();
    ~GestorNPCsUI();
    void setUp(QWidget* EscenarioDocumentos, QWidget *EscenarioNPCs, ColaNPC* cola);
    void setUpDocsIcono(QWidget * escena);
    void setUpTranscriptor(QPushButton * boton);

    DocsIconUI * getDocsIcono();
    void setUpNuevoNivel(int Nivel);

    void EmpezarJuego();

    // void addNpc(NPC* newNPC); A incluir a futuro si es necesario
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

    // Cosas de documentos (luego vemos como se arregla esto)
    void DetenerAnimacionesDocumentos();

public slots:
    void Dialogo(const QString &dialogo);
    void emitirNPCTerminoSalir();
    void emitColaTerminada();
    void CentrarDocumentos();
    void CentrarNPC();

signals:
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
    void SalirEntidades();

private:
    ColaNPC* ColaNPCs;
    QWidget* Escenario;
    GestorDocumentosUI GestorDocumentos;

    // NPCs
    NPCGenericoUI* NPCcomunUI;
    NPC* NPCenEscena;
    bool Rechazado;

    GlobosDialogoUI* Dialogos;

    bool MostrandoNPC;

    // Iconos de Docs
    DocsIconUI * docsIconUI;
    TranscriptorDialogos * transcriptorDialogos;

    int topeNPCs;
    int NivelActual;
    void RealizarConexionesDeNPCs();
    void DesconectarNPCs();
    bool NPCConectado;
    void ActualizarEstadoNPC();
};

#endif // GESTORNPCSUI_H
