#include "NPC.h"
#include <string>
using namespace std;

NPC::NPC(string Cara, char Gen){
    this->CaraURL = Cara;
    this->Genero = Gen;
}

void NPC::setDocumentacion(Documentacion* docs){
    this->documentos = docs;
}

string NPC::getCara(){
    return this->CaraURL;
}

char NPC::getGenero(){
    return this->Genero;
}

Documentacion* NPC::getDocumentos(){
    return this->documentos;
}


