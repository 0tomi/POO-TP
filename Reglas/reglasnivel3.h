#ifndef REGLASNIVEL3_H
#define REGLASNIVEL3_H
#include "reglas.h"

class ReglasNivel3: public Reglas
{
public:
    ReglasNivel3();
    void generar_MaxAcompaniantes();
    void set_MaxAcompaniantes(int);
    int getMaxAcompaniantes() const;
private:
    int maxAcompaniantes;
};

#endif // REGLASNIVEL3_H
