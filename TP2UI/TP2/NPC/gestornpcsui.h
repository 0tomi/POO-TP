#ifndef GESTORNPCSUI_H
#define GESTORNPCSUI_H

#include <QWidget>
#include "npcgenericoui.h"
#include "npccomun.h"
#include "../Generadores/colanpc.h"

class GestorNPCsUI: public QWidget
{
public:
    GestorNPCsUI();
    void setUp(QWidget *parent, ColaNPC* cola);
    void setUpNuevoNivel();
    // void addNpc(NPC* newNPC); A incluir a futuro si es necesario
    void Centrar();
    void Entrar();
    void Salir();
    void TerminoNivel();
    bool MostrandoElNPC();
    int NPCsRestantes();

public slots:
    void Rechazado();

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

private:
    ColaNPC* ColaNPCs;
    QWidget* Escenario;

    NPCGenericoUI* NPCcomunUI;
    NPC* NPCenEscena;

    bool MostrandoNPC;

    int topeNPCs;
    void RealizarConeccionesDeNPCs();
};

#endif // GESTORNPCSUI_H
