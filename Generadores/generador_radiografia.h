#include "../Reglas/reglasnivel5.h"

#ifndef GENERADOR_RADIOGRAFIA_H
#define GENERADOR_RADIOGRAFIA_H

class generador_Radiografia
{
private:
    ReglasNivel5 * rules;
    QRandomGenerator random;
public:
    generador_Radiografia();
    void inicializar(ReglasNivel5 * rules, quint32 semilla);

};

#endif // GENERADOR_RADIOGRAFIA_H
