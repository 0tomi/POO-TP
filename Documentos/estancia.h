#ifndef ESTANCIA_H
#define ESTANCIA_H

#include <QString>

#include "documentacion.h"

class Estancia: public Documentacion {
private:
    int duracionEst;
    QString tipoEst;
public:
    Estancia(int duracEst, QString tipoEst);

    // getters:
    int getDuracEstancia();
    QString getTipoEstancia();
};

#endif // ESTANCIA_H
