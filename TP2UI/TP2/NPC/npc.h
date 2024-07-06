#ifndef NPC_H
#define NPC_H

#include "../Documentos/documentacion.h"
#include <string>
using namespace std;

class NPC
{
public:
    explicit NPC(char Genero, char Tipo);
    ~NPC();

    virtual void setDocumentacion(Documentacion* docs);
    char getGenero();
    Documentacion* getDocumentos();
    char getTipo();

protected:

    char Genero;
    char Tipo;
    Documentacion* documentos;

};

#endif // NPC_H
