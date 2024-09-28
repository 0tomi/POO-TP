#ifndef NUEVAESTANCIA_H
#define NUEVAESTANCIA_H

#include "./estancia.h"

#include <vector>
#include <QString>

using namespace std;

class NuevaEstancia
{
public:
    NuevaEstancia();
    NuevaEstancia(Estancia* estancia, vector<QString> paisesPaso, vector<QString> bienesTransp, vector<QString> ocupacion);

    // getters:
    Estancia* getEstancia();
    vector<QString> getPaisesPaso();
    vector<QString> getBienesTransp();
    vector<QString> getOcupacion();
private:
    Estancia* estancia;
    vector<QString> paisesPaso;
    vector<QString> bienesTransp;
    vector<QString> ocupacion;
};

#endif // NUEVAESTANCIA_H
