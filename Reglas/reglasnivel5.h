#ifndef REGLASNIVEL5_H
#define REGLASNIVEL5_H
#include "reglasnivel4.h"

class ReglasNivel5: public Reglas
{
public:
    ReglasNivel5(Reglas *reglasNivel4);
    Reglas* reglasNivel4;
};

#endif // REGLASNIVEL5_H
