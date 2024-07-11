#ifndef GENERARESTANCIA_H
#define GENERARESTANCIA_H

#include <QString>
#include <QRandomGenerator>

#include "../Documentos/estancia.h"

class GenerarEstancia {
private:
    QRandomGenerator* NumRandom;
    bool valido;
    QString* tipoVisitas;
    int topeTipoVisitas;
    QString* tipoVisitasValidas;
    int topeVisitasValidas;
    int duracMaximaEstancia;
public:
    GenerarEstancia();
    ~GenerarEstancia();
    GenerarEstancia(QString* _tiposVisitas, int _topeTiposVisits, QString* _tiposVisitsVal, int _topeVisitsVal, int _duracMax);
    Estancia* getEstancia(bool valido); // Estancia a generar

    // getters
    QString* getTiposInvalidos(QString* tiposVisitas, QString* tiposVisitsVal, int &cantInvalidos);
};

#endif // GENERARESTANCIA_H
