#include "generadorDocs.h"
#include "../Niveles/reglas.cpp"

class ColaNPC{
public:
    ColaNPC(reglas* rules);
    void AddNPC(NPC* newNPC);
    NPC* GetNPC();
private:
    NPC* frente; 
    NPC* fondo;

    GeneradorNPC* GenerarNPC;
    GeneradorDocumentacion* GenerarDocumentacion;
};