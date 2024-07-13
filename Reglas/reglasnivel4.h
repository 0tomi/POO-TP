#ifndef REGLASNIVEL4_H
#define REGLASNIVEL4_H
#include "reglasnivel3.h"

class ReglasNivel4: public Reglas
{
public:
    ReglasNivel4(Reglas *reglasNivel3);
    Reglas *reglasNivel3;
};

#endif // REGLASNIVEL4_H
