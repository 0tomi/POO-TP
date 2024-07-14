#include "colanpc.h"
#include <ctime>
#include <QDebug>

ColaNPC::ColaNPC(AtributosComunes* datos, Reglas** rules){
    this->frente = this->fondo = NULL;
    this->size = 0;
    this->sizeOriginal = 0;
    this->GenerarDocumentacion = new GeneradorDocumentacion(datos ,rules);
    this->GenerarNPC = new GeneradorNPC;
    this->Random = new QRandomGenerator(time(NULL));
}

void ColaNPC::addNPC(int CantAldeano, int CantRefugiados, int CantDiplos, int CantRevolucionarios, int CantidadInvalidos)
{
    int totalNPCs = CantAldeano + CantRefugiados + CantDiplos + CantRevolucionarios;

    // Para simplificar el codigo vamos a usar un array que guarde los contadores de los tipos
    int arrayTipos[] = {CantAldeano, CantRefugiados, CantDiplos, CantRevolucionarios};

    // Tipos: 0 Aldeano, 1 Refugiado, 2 Diplomatico, 3 Revolucionario
    int sorteo = Random->bounded(4);
    int sorteoValidez = Random->bounded(20);
    bool Validez = true;

    while (totalNPCs){
        if (CantidadInvalidos)
            if (sorteoValidez > 13){
                Validez = false;
                CantidadInvalidos--;
            }
        if (arrayTipos[sorteo]){
            addNPC(sorteo, Validez); // Sumamos a la cola el npc con el tipo sorteado.
            arrayTipos[sorteo]--;
            totalNPCs--;
        }
        sorteo = Random->bounded(4);
        sorteoValidez = Random->bounded(20);
        Validez = true;
    }
}

void ColaNPC::addNPC(int Tipo, bool Validez){
    // Genero el NPC nuevo
    NPC* newNPC = GenerarNPC->getNPCgenerico(Tipo, Validez);
    // Genero su documentacion
    GenerarDocumentacion->getDocumentos(newNPC, Validez);
    // Genero el nodo de la cola donde estara el npc
    nodoNPC* newNode = new nodoNPC;
    newNode->info = newNPC;

    // Acomodamos la cola de NPCs
    if (this->size == 0){
        this->frente = this->fondo = newNode;
    } else {
        this->fondo->link = newNode;
        this->fondo = newNode;
    }

    size++;
    sizeOriginal++;
}

void ColaNPC::vaciarCola()
{
    nodoNPC* aux = this->frente;
    nodoNPC* aux2;
    while(aux != NULL){
        aux2 = aux->link;
        // Eliminamos el NPC
        delete aux->info;
        delete aux;

        aux = aux2;
    }

    this->sizeOriginal = 0;
    this->size = 0;
}

void ColaNPC::actualizarReglas(Reglas **newRules, int nivel)
{
    GenerarDocumentacion->actualizarReglas(newRules, nivel);
}

void ColaNPC::nextNivel(int Nivel)
{
    GenerarDocumentacion->nextNivel(Nivel);
}

NPC* ColaNPC::getNPC(){
    // Si la cola esta vacia
    if (this->size == 0)
        return NULL;

    // Se elimina el NPC anterior, si es que hay anterior.
    if (size < sizeOriginal)
        delete NPCaRetornar;

    nodoNPC* node2remove = frente;
    NPCaRetornar = frente->info;

    frente = frente->link;
    delete node2remove;
    size--;

    return NPCaRetornar;
}

int ColaNPC::getSize() const
{
    return size;
}

ColaNPC::~ColaNPC()
{
    this->vaciarCola();
    delete NPCaRetornar;
    delete Random;
    delete GenerarNPC;
    delete GenerarDocumentacion;
}
