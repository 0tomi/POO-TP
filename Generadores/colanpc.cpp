#include "colanpc.h"
#include <QTime>
#include <QDebug>

/// #################################### CONSTRUCTOR ###################################################
ColaNPC::ColaNPC():
    Random(QTime::currentTime().msec()), GenerarNPC(&Random), GenerarDocumentacion()
{
    this->size = 0;
}

void ColaNPC::setSeed(quint32 seed)
{
    this->semillaActual = seed;
    Random.seed(seed);
    GenerarNPC.setSeed(seed);
    GenerarDocumentacion.setSeed(seed);
}

void ColaNPC::Inicializar(int Nivel, int Dificultad, Reglas **rules, quint32 seed)
{
    // Aca irian las reglas que le pase juego al leer los niveles
    this->setSeed(seed);
    GenerarNPC.setSeed(seed);
    GenerarDocumentacion.Inicializar(Nivel, Dificultad, rules, this->semillaActual);
}

ColaNPC::~ColaNPC()
{
    this->vaciarCola();
}

/// #################################### Añadir NPCs a cola ###################################################
void ColaNPC::addNPC(int NivelActual, int CantAldeano, int CantRefugiados, int CantDiplos, int CantRevolucionarios, int CantidadInvalidos)
{
    this->size = 0;
    // Preparamos que nivel se usara.
    nivelActual = NivelActual;
    setNivel(nivelActual);

    int totalNPCs = CantAldeano + CantRefugiados + CantDiplos + CantRevolucionarios;

    // Para simplificar el codigo vamos a usar un array que guarde los contadores de los tipos
    int arrayTipos[] = {CantAldeano, CantRefugiados, CantDiplos, CantRevolucionarios};

    // Tipos: 0 Aldeano, 1 Refugiado, 2 Diplomatico, 3 Revolucionario
    int sorteo = Random.bounded(4);
    int sorteoValidez = Random.bounded(20);
    bool Validez = true;

    qDebug() << "Bucle de generar NPCs";
    while (totalNPCs){
        // Si hay NPCs invalidos a colocar, sorteamos y decidimos si se generaran en la iteracion.
        if (CantidadInvalidos)
            if (sorteoValidez > 11){
                Validez = false;
                CantidadInvalidos--;
            }
        // Genera el tipo de NPC, basado en si el contador llego a 0; si llega a 0 no genera mas npcs de ese tipo.
        if (arrayTipos[sorteo]){
            addNPC(sorteo, Validez); // Sumamos a la cola el npc con el tipo sorteado.
            arrayTipos[sorteo]--;
            totalNPCs--;            // Restamos el contador de tipos de npc, y el total.
        }
        sorteo = Random.bounded(4);
        sorteoValidez = Random.bounded(20);
        Validez = true;
    }
}

void ColaNPC::addNPC(int Tipo, bool Validez){
    // Genero el NPC nuevo
    NPC* newNPC = GenerarNPC.getNPCgenerico(Tipo, Validez, nivelActual); // A futuro actualizar para que reciba el nivel

    // Genero su documentacion
    GenerarDocumentacion.getDocumentos(newNPC, Validez); // A futuro actualizar para que reciba el nivel

    // Generamos el dialogo del npc
    GenerarNPC.generarDialogos(newNPC, nivelActual);

    VectorNPCs.push_back(newNPC);
    size++;
}
/// #################################### Vaciar cola ###################################################
void ColaNPC::vaciarCola()
{
    for (NPC* ptr: VectorNPCs)
        delete ptr;
    VectorNPCs.clear();

    this->size = 0;
}

/// #################################### Setters ###################################################
void ColaNPC::setDificultad(int newDificultad)
{
    GenerarDocumentacion.setDificultad(newDificultad);
}

void ColaNPC::setNivel(int Nivel)
{
    GenerarDocumentacion.setNivel(Nivel);
}

/// #################################### GETTERS ###################################################
NPC* ColaNPC::getNPC(){
    NPCaRetornar = VectorNPCs[size-1];
    size--;

    return NPCaRetornar;
}

int ColaNPC::getSize() const
{
    return size;
}


