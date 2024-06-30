#include "Estancia.h"
#include "Pasaporte.h"

#ifndef DOC_H
#define DOC_H
class Documentacion{
private:
  Pasaporte* pasaport;
  Estancia* estancia;
public:
  bool valida;
};

#endif // !DOC_H

