#ifndef COLANPC_H
#define COLANPC_H

#include "generadordocumentacion.h"
#include "generadornpc.h"
#include "../Reglas/reglasnivel5.h"
#include <QRandomGenerator>

class ColaNPC{
public:
    ColaNPC();
    void setSeed(quint32 seed);
    void Inicializar(int Nivel, int Dificultad, Reglas ** rules, quint32 seed);
    void setUpColaEmpezada(int cantidad_NPCs_pasados);

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

    int getCantidadNPCsFalsos() const;

private:
    struct dupla{
        int Tipo;
        bool Validez;
    };
    vector <dupla> NPCSaGenerar;

    bool GenerarNPCs(int CantidadTotal, int CantidadFalsos, int CantidadTipos[]);
    quint32 semillaActual;
    vector<NPC*> VectorNPCs;
    int size;
    int cantidadNPCsFalsos;
    int nivelActual;

    NPC* NPCaRetornar;

    QRandomGenerator Random;

    GeneradorNPC GenerarNPC;
    GeneradorDocumentacion GenerarDocumentacion;
};

#endif // COLANPC_H
