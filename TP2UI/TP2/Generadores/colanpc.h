#ifndef COLANPC_H
#define COLANPC_H

#include "generadordocumentacion.h"
#include "generadornpc.h" // a futuro para que tengan las cosas de los npcs
#include "../Reglas/reglas.h"
#include "../AtributosComunes/atributoscomunes.h"

struct nodoNPC{
    NPC* info;
    nodoNPC* link = NULL;
};

class ColaNPC{
public:
    ColaNPC(AtributosComunes* atributos, reglas* rules);
    void addNPC();

    // Vaciar cola tiene que eliminar los NPCS restantes, junto con sus documentos y demas
    void vaciarCola();
    void actualizarReglas(reglas* rules);

    NPC* getNPC();
    int getSize();

private:
    nodoNPC* frente;
    nodoNPC* fondo;
    int size;

    GeneradorNPC* GenerarNPC;
    GeneradorDocumentacion* GenerarDocumentacion;
};

#endif // COLANPC_H