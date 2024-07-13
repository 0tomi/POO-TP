#ifndef REGLASNIVEL3_H
#define REGLASNIVEL3_H
#include "reglasnivel2.h"

class ReglasNivel3: public Reglas
{
public:
    ReglasNivel3(Reglas* reglasNivel2);
    Reglas* reglasNivel2;
};

#endif // REGLASNIVEL3_H
