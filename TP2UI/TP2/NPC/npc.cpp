#include "npc.h"

NPC::NPC(char Gen, char Type){
    this->Genero = Gen;
    this->Tipo = Type;
}

void NPC::setDocumentacion(Documentacion* docs){
    this->documentos = docs;
}

char NPC::getGenero(){
    return this->Genero;
}

Documentacion* NPC::getDocumentos(){
    return this->documentos;
}

char NPC::getTipo()
{
    return Tipo;
}

NPC::~NPC()
{
    delete documentos;
    // y otras cosas si hace falta
}
