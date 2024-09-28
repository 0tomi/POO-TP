#ifndef GENERADOR_NUEVAESTANCIA_H
#define GENERADOR_NUEVAESTANCIA_H

#include "../Reglas/reglasnivel1.h"
#include "../Reglas/reglasnivel4.h"
#include "../Documentos/estancia.h"
#include "../Documentos/nuevaestancia.h"

#include <vector>
#include <QString>

class Generador_NuevaEstancia
{
public:
    Generador_NuevaEstancia();
    ~Generador_NuevaEstancia();
    void inicializadorNivel4(ReglasNivel1* reglasLvl1, ReglasNivel4* reglasLvl4, Estancia* estanciaOld);
    NuevaEstancia* getNuevaEstancia(bool valido, int dificultad);

private:
    Estancia* estancia;
    vector<QString> paisesPaso;
    vector<QString> bienesTransp;
    QString ocupacion;
};

#endif // GENERADOR_NUEVAESTANCIA_H
