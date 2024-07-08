#include "npc.h"

NPC::NPC(char Gen, int Type, bool newValidez){
    this->Genero = Gen;
    this->Tipo = Type;
    this->Validez = newValidez;
    for (int i = 0; i < 10; i++)
        documentos[i] = nullptr;
}

char NPC::getGenero(){
    return this->Genero;
}

Documentacion** NPC::getDocumentos(){
    // aca setearia los distintos documentos
    documentos[0] = pasaporte;
    documentos[1] = estancia;


    return documentos;
}

int NPC::getTipo()
{
    return Tipo;
}

bool NPC::getValidez() const
{
    return Validez;
}

void NPC::setPasaporte(Pasaporte *newPasaporte)
{
    pasaporte = newPasaporte;
}

void NPC::setEstancia(Estancia *newEstancia)
{
    estancia = newEstancia;
}

NPC::~NPC()
{
    delete pasaporte;
    delete estancia;
    // y otras cosas si hace falta
}
