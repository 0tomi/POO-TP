#include "gestorfondonpcs.h"

GestorFondoNPCs::GestorFondoNPCs() {
    this->cantidadNPCsFondo = this->cantidadNPCs = 0;
}

void GestorFondoNPCs::setUp(QWidget *Fondo)
{
    this->fondo = Fondo;
}

void GestorFondoNPCs::setSeed(quint32 seed)
{
    random.seed(seed);
}

GestorFondoNPCs::~GestorFondoNPCs()
{
    this->clear();
}

void GestorFondoNPCs::start(int CantNPCs)
{
    this->clear();
    int cantidad_spawnear = this->fondo->width() / 130;
    if (CantNPCs < 12)
        cantidad_spawnear = CantNPCs;
    this->cantidadNPCsFondo = cantidad_spawnear;

    npcs.resize(cantidad_spawnear);

    // Calculamos desde donde empezar a colocar los npcs, 130 es la cantidad de pixeles que ocupan.
    int x = this->fondo->width() - (cantidad_spawnear * 130);
    for (auto& npc: npcs){
        npc = new NPCFondo(&random, this->fondo);
        npc->move(QPoint(x, npc->y()));
        x += npc->width() + 15;
        connect(npc, &NPCFondo::Salio, this, &GestorFondoNPCs::NPCterminoSalir);
        connect(npc, &NPCFondo::Posicion, this, &GestorFondoNPCs::NPCactualizoPosicion);
    }

    this->ultimoNPCenSalir = cantidad_spawnear-1;
    npcs[ultimoNPCenSalir]->setPrimero(true);
}

void GestorFondoNPCs::NPCactualizoPosicion(QPoint p)
{
    //for (auto &npc: npcs)
        //npc->updateLocation(p);
}

void GestorFondoNPCs::clear()
{
    for (auto& npc: npcs)
        if (npc) delete npc;
    npcs.clear();
}

void GestorFondoNPCs::updateCantidadNPCs(int cantidad)
{
    this->cantidadNPCs = cantidad;
}

void GestorFondoNPCs::resizeNPCs()
{
    if (npcs.size() == 0)
        return;


    for (auto &npc : npcs){
        int y = fondo->height() - npc->height();
        if (!npc->isHidden())
            npc->move(npc->x(), y);
    }
}

void GestorFondoNPCs::pasarNPC()
{
    for (auto &npc: npcs)
        npc->moverAdelante();
}

void GestorFondoNPCs::NPCterminoSalir()
{
    if (cantidadNPCs == 0)
        return;

    if (this->cantidadNPCs >= cantidadNPCsFondo)
        npcs[ultimoNPCenSalir]->volverEntrar();
    else cantidadNPCsFondo = this->cantidadNPCs;

    ultimoNPCenSalir--;
    if (ultimoNPCenSalir == -1)
        ultimoNPCenSalir = npcs.size()-1;

    if (npcs[ultimoNPCenSalir]->isHidden())
        // buscamos el proximo npc que va a salir en caso de llegar al npc 0.
        for (int i = npcs.size(); npcs[i]->isHidden() || i >= 0; i--)
            ultimoNPCenSalir = i;


    npcs[ultimoNPCenSalir]->setPrimero(true);
}
