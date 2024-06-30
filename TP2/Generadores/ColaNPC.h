#include "generadorDocs.h"
#include "../Niveles/reglas.cpp"
#include "../AtributosComun/AtributosComunes.cpp"

class ColaNPC{
public:
    ColaNPC(reglas* rules, AtributosComunes atributos);
    void AddNPC(NPC* newNPC);
    NPC* GetNPC();
private:
    NPC* frente; 
    NPC* fondo;
    int size;

    GeneradorNPC* GenerarNPC;
    GeneradorDocumentacion* GenerarDocumentacion;
};