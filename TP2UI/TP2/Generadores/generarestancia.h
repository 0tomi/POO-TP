#ifndef GENERARESTANCIA_H
#define GENERARESTANCIA_H

#include <QString>
#include <QRandomGenerator>

#include "../Documentos/estancia.h"

class GenerarEstancia {
private:
    QRandomGenerator* random;
    bool valido;
    QString* tipoVisitas;
    int topeTipoVisitas;
    QString* tipoVisitasValidas;
    int topeVisitasValidas;
    int duracMaximaEstancia;
public:
    GenerarEstancia();
    GenerarEstancia(QString*, int, QString*, int, int);
    Estancia* getEstancia(bool valido); // Estancia a generar

    // getters
    QString* getTiposInvalidos(QString* tiposVisitas, QString* tiposVisitsVal, int &cantInvalidos);
    int getTopeTipoVisitas();
    int getTopeTipoVisitasVals();
    bool getValidacion();
};

#endif // GENERARESTANCIA_H
