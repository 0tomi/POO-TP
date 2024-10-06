#ifndef ESTANCIA_H
#define ESTANCIA_H

#include <QString>

#include "documentacion.h"

class Estancia: public Documentacion {
private:
    int duracionEst;
    QString tipoEst;
    bool Validez;
public:
    Estancia(int duracEst, QString tipoEst, bool valido);

    // getters:
    int getDuracEstancia();
    QString getTipoEstancia();
    bool getValidez() const;
};

#endif // ESTANCIA_H
