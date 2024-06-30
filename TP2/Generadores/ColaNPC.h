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