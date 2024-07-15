#ifndef GESTORNPCSUI_H
#define GESTORNPCSUI_H

#include <QWidget>
#include <QTimer>
#include "../NPC/npcgenericoui.h"
#include "../NPC/npccomun.h"
#include "../NPC/globosdialogoui.h"
#include "../Generadores/colanpc.h"
#include "gestordocumentosui.h"

class GestorNPCsUI: public QWidget
{
    Q_OBJECT

public:
    GestorNPCsUI();
    ~GestorNPCsUI();
    void setUp(QWidget* EscenarioDocumentos, QWidget *EscenarioNPCs, ColaNPC* cola);
    void setUpNuevoNivel(int Nivel);
    // void addNpc(NPC* newNPC); A incluir a futuro si es necesario
    void Centrar();
    void Entrar();
    void Salir();

    void TerminoNivel();
    bool MostrandoElNPC() const;

    int NPCsRestantes();

    bool getValidez();
    int getTipo();

    // Cosas de documentos (luego vemos como se arregla esto)
    void DetenerAnimacionesDocumentos();
    void DocRechazado();
    void DocAprobado();

public slots:
    void Rechazado();
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
    void EntrarEntidades();

private:
    ColaNPC* ColaNPCs;
    QWidget* Escenario;
    GestorDocumentosUI GestorDocumentos;

    NPCGenericoUI* NPCcomunUI;
    NPC* NPCenEscena;

    GlobosDialogoUI* Dialogos;

    bool MostrandoNPC;
    QTimer EntrarNPCsYDocs;

    int topeNPCs;
    int NivelActual;
    void RealizarConeccionesDeNPCs();
    void RealizarDesconeccionesNPC();
    void ActualizarEstadoNPC();
};

#endif // GESTORNPCSUI_H
