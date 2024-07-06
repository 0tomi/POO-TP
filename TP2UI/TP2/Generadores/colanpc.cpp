#include "colanpc.h"

ColaNPC::ColaNPC(AtributosComunes* datos, Reglas* rules){
    this->frente = this->fondo = NULL;
    this->size = 0;
    this->GenerarDocumentacion = new GeneradorDocumentacion(datos ,rules);
    this->GenerarNPC = new GeneradorNPC;
}

void ColaNPC::addNPC(char Tipo){
    // Genero el NPC nuevo
    NPC* newNPC = this->GenerarNPC->getNPCgenerico(Tipo);
    // Genero su documentacion
    newNPC->setDocumentacion(this->GenerarDocumentacion->getDocumentos(newNPC));
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

    this->size++;
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

void ColaNPC::addNPC(int CantAldeano, int CantRefugiados, int CantDiplos, int CantRevolucionarios)
{
    int totalNPCs = CantAldeano + CantRefugiados + CantDiplos + CantRevolucionarios;

    // Para simplificar el codigo vamos a usar un array que guarde los contadores de los tipos
    int arrayTipos[] = {CantAldeano, CantRefugiados, CantDiplos, CantRevolucionarios};

    // Tipos: 0 Aldeano, 1 Refugiado, 2 Diplomatico, 3 Revolucionario
    int sorteo = rand()%4;

    while (totalNPCs){
        if (!(arrayTipos[sorteo])) // Si el contador es 0, activara el if, y sorteara otro tipo.
            sorteo = rand()%4;
        else{
            addNPC(sorteo); // Sumamos a la cola el npc con el tipo sorteado.
            arrayTipos[sorteo]--;
            totalNPCs--;
        }
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
    this->size--;

    return npc;
}

int ColaNPC::getSize(){
    return this->size;
}
