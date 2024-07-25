#include <QString>
#ifndef PAISDERESIDENCIA_H
#define PAISDERESIDENCIA_H

class PaisDeResidencia
{
    QString nombre;
    QString fecha_nacimiento;
    char genero;
    QString nacionalidad;
    QString PaisdeResidencia;
public:
    PaisDeResidencia(QString nombre, QString fecha, char genero, QString nacionalidad,QString PaisdeResidencia);
    QString getNombre() const;
    QString getFecha() const;
    char getGenero() const;
    QString getNacionalidad() const;
    QString getPaisdeResidencia() const;
};

#endif // PAISDERESIDENCIA_H
