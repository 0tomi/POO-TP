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
    void addNpc(NPC* newNPC);
    void Centrar();
    void Entrar();
    void Salir();
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
    NPC Npcs;
    int topeNPCs;
};

#endif // GESTORNPCSUI_H
