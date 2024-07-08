#ifndef COLANPC_H
#define COLANPC_H

#include "generadordocumentacion.h"
#include "generadornpc.h" // a futuro para que tengan las cosas de los npcs
#include "../Reglas/reglasnivel5.h"
#include "../AtributosComunes/atributoscomunes.h"
#include <QRandomGenerator>

struct nodoNPC{
    NPC* info;
    nodoNPC* link = NULL;
};

class ColaNPC{
public:
    ColaNPC(AtributosComunes* atributos, Reglas* rules);
    void addNPC(int Tipo, bool Validez);
    void addNPC(int CantAldeano, int CantRefugiados, int CantDiplos, int CantRevolucionarios, int CantidadInvalidos);

    // A futuro para cuando tengamos NPCs especiales
    void addNPC(int CantAldeanos, int CantRefugiados, int CantDiplos, int CantRev, int CantEspeciales, int CantidadInvalidos);
    void addSpecialNPC(string nombreNPC);

    // Vaciar cola tiene que eliminar los NPCS restantes, junto con sus documentos y demas
    void vaciarCola();
    void actualizarReglas(Reglas* rules, int nivel);

    NPC* getNPC();

    int getSize() const;

private:
    nodoNPC* frente;
    nodoNPC* fondo;
    int size;

    QRandomGenerator *Random;
    Reglas* reglas;

    GeneradorNPC* GenerarNPC;
    GeneradorDocumentacion* GenerarDocumentacion;
};

#endif // COLANPC_H
