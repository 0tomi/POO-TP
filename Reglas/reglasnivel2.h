#ifndef REGLASNIVEL2_H
#define REGLASNIVEL2_H
#include "reglasnivel1.h"


class ReglasNivel2: public Reglas
{
public:
    ReglasNivel2(Reglas* reglasLvL1);
    Reglas* reglasNivel1;
};

#endif // REGLASNIVEL2_H
