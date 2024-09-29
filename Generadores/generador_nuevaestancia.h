#ifndef GENERADOR_NUEVAESTANCIA_H
#define GENERADOR_NUEVAESTANCIA_H

#include "../Reglas/reglasnivel1.h"
#include "../Reglas/reglasnivel4.h"
#include "../Documentos/estancia.h"
#include "../Documentos/nuevaestancia.h"

#include <vector>
#include <QString>
#include <QRandomGenerator>

class Generador_NuevaEstancia
{
public:
    Generador_NuevaEstancia();
    ~Generador_NuevaEstancia();
    void inicializadorNivel4(ReglasNivel1* reglasLvl1, ReglasNivel4* reglasLvl4, Estancia* estanciaOld, quint32 intSeed);
    NuevaEstancia* getNuevaEstancia(bool valido, int dificultad);

    vector<QString> generar_paisesPaso(bool valido);
    vector<QString> generar_bienesTransp(bool valido);
    vector<QString> generar_ocupacion(bool valido);
private:
    Estancia* estancia;
    vector<QString> paisesPaso;
    //vector<QString> paisesPasoInvalidos;
    vector<QString> bienesTransp;
    //vector<QString> bienesTranspInvalidos;
    vector<QString> ocupacion;
    //vector<QString> ocupacionInvalida;

    ReglasNivel1* reglasLvl1;
    ReglasNivel4* reglasLvl4;

    QRandomGenerator random;
};

#endif // GENERADOR_NUEVAESTANCIA_H
