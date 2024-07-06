#ifndef DOCUMENTACION_H
#define DOCUMENTACION_H
#include "estancia.h"
#include "pasaporte.h"

class Documentacion
{
public:
    Documentacion(bool validez);
    ~Documentacion();

    bool getValida() const;
    Pasaporte *getPasaport() const;
    void setPasaport(Pasaporte *newPasaport);
    Estancia *getEstancia() const;
    void setEstancia(Estancia *newEstancia);

private:
    Pasaporte* pasaport;
    Estancia* estancia;
    bool valida;
};

#endif // DOCUMENTACION_H
