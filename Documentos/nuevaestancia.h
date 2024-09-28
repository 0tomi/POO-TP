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
    NuevaEstancia(Estancia* estancia, vector<QString> paisesPaso, vector<QString> bienesTransp, QString ocupacion);

    // getters:
    Estancia* getEstancia();
    vector<QString> getPaisesPaso();
    vector<QString> getBienesTransp();
    QString getOcupacion();
private:
    Estancia* estancia;
    vector<QString> paisesPaso;
    vector<QString> bienesTransp;
    QString ocupacion;
};

#endif // NUEVAESTANCIA_H
