#ifndef COLANPC_cpp
#define COLANPC_cpp

#include "colanpc.h"
ColaNPC::ColaNPC(AtributosComunes* datos, reglas* rules){
    this->frente = this->fondo = NULL;
    this->size = 0;
    this->GenerarDocumentacion = new GeneradorDocumentacion(datos ,rules);
    this->GenerarNPC = new GeneradorNPC;
}

void ColaNPC::addNPC(){
    // Genero el NPC nuevo
    NPC* newNPC = this->GenerarNPC->getNPC();
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
#endif
