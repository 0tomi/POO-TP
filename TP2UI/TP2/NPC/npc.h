#ifndef NPC_H
#define NPC_H

#include "../Documentos/documentacion.h"
#include <string>
using namespace std;

class NPC
{
public:
    NPC(string CaraURL, char Genero);
    void setDocumentacion(Documentacion* docs);

    string getCara();
    char getGenero();
    Documentacion* getDocumentos();
private:
    string CaraURL;
    char Genero;
    Documentacion* documentos;
};

#endif // NPC_H
