#ifndef COLANPC_H
#define COLANPC_H

#include "generadordocumentacion.h"
#include "generadornpc.h"
#include "../Reglas/reglasnivel5.h"
#include <QRandomGenerator>

class ColaNPC{
public:
    ColaNPC();
    void Inicializar(int Nivel, int Dificultad, Reglas ** rules);

    void addNPC(int Tipo, bool Validez);
    void addNPC(int NivelActual, int CantAldeano, int CantRefugiados, int CantDiplos, int CantRevolucionarios, int CantidadInvalidos);

    /// A futuro para cuando tengamos NPCs especiales
    //void addNPC(int NivelActual, int CantAldeanos, int CantRefugiados, int CantDiplos, int CantRev, int CantEspeciales, int CantidadInvalidos);
    //void addSpecialNPC(string nombreNPC);

    // Vaciar cola tiene que eliminar los NPCS restantes, junto con sus documentos y demas
    void vaciarCola();
    void setNivel(int Nivel);
    void setDificultad(int Dificultad);

    NPC* getNPC();
    int getSize() const;

    ~ColaNPC();

private:
    vector<NPC*> VectorNPCs;
    int sizeOriginal;
    int size;
    int nivelActual;

    NPC* NPCaRetornar;

    QRandomGenerator Random;

    GeneradorNPC GenerarNPC;
    GeneradorDocumentacion GenerarDocumentacion;
};

#endif // COLANPC_H
