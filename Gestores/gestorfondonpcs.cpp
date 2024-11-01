#include "gestorfondonpcs.h"

GestorFondoNPCs::GestorFondoNPCs() {
    this->cantidadNPCsFondo = this->cantidadNPCs = 0;
    npcs.resize(10);
    for (auto &npc: npcs)
        npc = nullptr;
}

void GestorFondoNPCs::setUp(QWidget *Fondo)
{
    this->fondo = Fondo;
}

GestorFondoNPCs::~GestorFondoNPCs()
{
    this->clear();
}

void GestorFondoNPCs::start(int CantNPCs)
{
    int cantidad_spawnear = 10;
    if (CantNPCs < 10)
        cantidad_spawnear = CantNPCs;

    int x = 0;
    for (auto& npc: npcs){
        npc = new NPCFondo(this->fondo);
        npc->move(QPoint(x, npc->y()));
        x += npc->width() + 15;
    }
}

void GestorFondoNPCs::clear()
{
    for (auto& npc: npcs)
        if (npc) delete npc;
}

void GestorFondoNPCs::updateCantidadNPCs(int)
{

}

void GestorFondoNPCs::resizeNPCs()
{

}

void GestorFondoNPCs::pasarNPC()
{

}
