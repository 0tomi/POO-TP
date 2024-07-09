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

void NPC::addDocumento(Documentacion *newDoc, int Index)
{
  /*
    Codigos internos de documentacion: (El pase diplomatico no esta incluido, todavia)
    0: Pasaporte
    1: Dni
    2: Estancia
    3: <a desarrollar>
    4: <a desarrollar>
    5: <a desarrollar>
    6: <a desarrollar>
    7: <a desarrollar>
    8: <a desarrollar>
    9: <a desarrollar>
  */

    documentos[Index] = newDoc;
}

NPC::~NPC()
{
    for (int i = 0; i < 10; i++)
        delete documentos[i];
}
