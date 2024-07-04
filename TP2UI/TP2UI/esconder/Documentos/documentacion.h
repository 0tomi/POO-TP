#ifndef DOCUMENTACION_H
#define DOCUMENTACION_H
#include "estancia.h"
#include "pasaporte.h"

class Documentacion{
private:
    Pasaporte* pasaport;
    Estancia* estancia;
public:
    bool valida;
    Documentacion();
};

#endif // DOCUMENTACION_H
