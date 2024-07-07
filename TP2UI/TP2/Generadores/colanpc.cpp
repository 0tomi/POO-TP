#include "colanpc.h"
#include <ctime>
#include <QDebug>

ColaNPC::ColaNPC(AtributosComunes* datos, Reglas* rules){
    this->frente = this->fondo = NULL;
    this->size = 0;
    this->GenerarDocumentacion = new GeneradorDocumentacion(datos ,rules);
    this->GenerarNPC = new GeneradorNPC;
}

void ColaNPC::addNPC(char Tipo, bool Validez ,unsigned int Semilla){
    // Genero el NPC nuevo
    qDebug() << Semilla;
    NPC* newNPC = this->GenerarNPC->getNPCgenerico(Tipo, Semilla, Validez);
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

}

void ColaNPC::addNPC(int CantAldeano, int CantRefugiados, int CantDiplos, int CantRevolucionarios, int CantidadInvalidos)
{
    unsigned int Semilla = time(NULL);

    int totalNPCs = CantAldeano + CantRefugiados + CantDiplos + CantRevolucionarios;

    // Para simplificar el codigo vamos a usar un array que guarde los contadores de los tipos
    int arrayTipos[] = {CantAldeano, CantRefugiados, CantDiplos, CantRevolucionarios};

    // Tipos: 0 Aldeano, 1 Refugiado, 2 Diplomatico, 3 Revolucionario
    int sorteo = rand()%4;
    int sorteoValidez = rand()%20;
    bool Validez;

    while (totalNPCs){
        if (CantidadInvalidos)
            if (sorteoValidez > 15){
                Validez = false;
                CantidadInvalidos--;
            }
        if (!(arrayTipos[sorteo])){ // Si el contador es 0, activara el if, y sorteara otro tipo.
            sorteo = rand()%4;
        } else {
            addNPC(sorteo, Validez, Semilla); // Sumamos a la cola el npc con el tipo sorteado.
            arrayTipos[sorteo]--;
            totalNPCs--;
            Semilla += 5; // para añadir mas aleatoriedad al asunto
        }
        sorteoValidez = rand()%20;
    }
}

NPC* ColaNPC::getNPC(){
    // Si la cola esta vacia
    if (this->size == 0)
        return NULL;

    nodoNPC* node2remove = frente;
    NPC* npc = frente->info;

    frente = frente->link;
    delete node2remove;
    size--;

    return npc;
}

int ColaNPC::getSize() const
{
    return size;
}
