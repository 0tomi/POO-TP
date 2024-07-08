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
    char getTipo();

    bool getValidez() const;

    virtual void setPasaporte(Pasaporte *newPasaporte);
    virtual void setEstancia(Estancia *newEstancia);

protected:
    bool Validez;
    char Genero;
    char Tipo;
    Documentacion* documentos[10];
    Pasaporte *pasaporte = nullptr;
    Estancia *estancia = nullptr;
};

#endif // NPC_H
