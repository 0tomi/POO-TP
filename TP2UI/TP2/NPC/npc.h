#ifndef NPC_H
#define NPC_H

#include "../Documentos/pasaporte.h"
#include "../Documentos/estancia.h"
#include <string>
using namespace std;

class NPC
{
public:
    explicit NPC(char Genero, int Tipo, bool Validez);
    ~NPC();

    char getGenero();
    Documentacion** getDocumentos();
    int getTipo();

    bool getValidez() const;

    void addDocumento(Documentacion *newDoc, int Index);

protected:
    bool Validez;
    char Genero;
    int Tipo;
    Documentacion* documentos[10];
};

#endif // NPC_H
