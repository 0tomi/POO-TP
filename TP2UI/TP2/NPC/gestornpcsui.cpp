#include "gestornpcsui.h"
#include <QLayout>

GestorNPCsUI::GestorNPCsUI(){

}

void GestorNPCsUI::setUp(QWidget *parent, ColaNPC *cola)
{
    Escenario = parent;
    ColaNPCs = cola;

    // Spawneamos NPC
    NPCcomunUI = new NPCGenericoUI(Escenario);
    Escenario->layout()->addWidget(NPCcomunUI);

    // ## A futuro iria aca el setup del NPC especial. ##

    RealizarConeccionesDeNPCs();
    // Colocamos al NPC fuera del escenario para iniciar la cinematica.
    NPCcomunUI->hide();
    NPCcomunUI->move(-(NPCcomunUI->width()),0);
    MostrandoNPC = false;
}

void GestorNPCsUI::setUpNuevoNivel()
{
    RealizarConeccionesDeNPCs();
}

void GestorNPCsUI::Centrar()
{
    // ### Aca iria un IF para checkear si el NPC es de tipo especial o comun, y decidir cual setear.
    int centerX = (Escenario->width() - NPCcomunUI->width()) /2;
    int centerY = (Escenario->height()) - (NPCcomunUI->height());
    NPCcomunUI->move(centerX,centerY);
}

void GestorNPCsUI::Entrar()
{
    if (ColaNPCs->getSize() == 0){
        TerminoNivel();
        return;
    } else if (ColaNPCs->getSize() == 1) {
            emit UltimoNPC();
    }

    NPCenEscena = ColaNPCs->getNPC();

    // ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ##
    qDebug() << NPCenEscena->getGenero();
    qDebug() << NPCenEscena->getTipo();
    qDebug() << NPCenEscena->getValidez();
    // ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ##

    // ### Aca iria un IF para checkear si el NPC es de tipo especial o comun, y decidir cual setear.
    NPCcomunUI->setNPC(NPCenEscena);

    int centerX = (Escenario->width() - NPCcomunUI->width()) / 2;
    int centerY = Escenario->height() - NPCcomunUI->height();

    NPCcomunUI->Entrar(centerX, centerY);
    MostrandoNPC = true;
}

void GestorNPCsUI::Salir()
{
    // ### Aca iria un IF para checkear si el NPC es de tipo especial o comun, y decidir cual setear.
    int SalidaEscena = Escenario->width() + NPCcomunUI->width();
    int centerY = (Escenario->height()) - (NPCcomunUI->height()) + 50;
    NPCcomunUI->Sacar(SalidaEscena, centerY);
    MostrandoNPC = false;
}

void GestorNPCsUI::TerminoNivel()
{
    disconnect(NPCcomunUI, &NPCUI::animacionSalirTerminada, this, &GestorNPCsUI::Entrar);
    // ### Aca iria disconnect del NPC Especial

    if (ColaNPCs->getSize() != 0)
        ColaNPCs->vaciarCola();
    emit ColaTerminada();
}

bool GestorNPCsUI::MostrandoElNPC() const
{
    return MostrandoNPC;
}

int GestorNPCsUI::NPCsRestantes() const
{
    return ColaNPCs->getSize();
}

void GestorNPCsUI::Rechazado()
{
    // ### Aca iria un IF para checkear si el NPC es de tipo especial o comun, y decidir cual setear.
    NPCcomunUI->Rechazado();
}

void GestorNPCsUI::RealizarConeccionesDeNPCs()
{
    // Hago que al terminar la animacion de que un NPC se va, entre otro.
    connect(NPCcomunUI, &NPCUI::animacionEntrarTerminada, this, &GestorNPCsUI::Centrar);

    // Hago que al terminar la animacion de que un NPC se va, entre otro.
    connect(NPCcomunUI, &NPCUI::animacionSalirTerminada, this, &GestorNPCsUI::Entrar);

    // Aca irian las conecciones del NPC especial
}
