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
    virtual ~NPC();

    virtual char getGenero();
    virtual Documentacion** getDocumentos();
    virtual int getTipo();
    virtual bool getValidez() const;

    virtual void addDocumento(Documentacion *newDoc, int Index);

protected:
    bool Validez;
    char Genero;
    int Tipo;
    Documentacion* documentos[10];
};

#endif // NPC_H
