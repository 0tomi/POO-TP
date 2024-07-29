#include <QString>
#include "documentacion.h"
#ifndef PAISRESIDENCIA_H
#define PAISRESIDENCIA_H

class PaisResidencia : public Documentacion
{
private:
    QString nombre;
    QString fecha_nacimiento;
    QString PaisDeResidencia;
public:
    PaisResidencia(QString nombre,QString fecha,QString PaisDeResidencia);
    QString getNombre() const;
    QString getFecha() const;
    QString getPaisResidencia() const;
};

#endif // PAISRESIDENCIA_H
