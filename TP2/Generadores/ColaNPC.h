#include "generadorDocs.h"
#include "../Niveles/reglas.cpp"
#include "../AtributosComun/AtributosComunes.cpp"

#ifndef COLANPC_H
#define COLANPC_H

struct nodoNPC{
    NPC* info;
    nodoNPC* link = NULL;
};

class ColaNPC{
public:
    ColaNPC(AtributosComunes* atributos, reglas* rules);
    void addNPC(NPC* newNPC);
    
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
#endif // !COLANPC_H