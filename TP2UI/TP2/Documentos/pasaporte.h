#ifndef PASAPORTE_H
#define PASAPORTE_H
#include "documentacion.h"

#include <string>
#include <QLabel>
class Pasaporte : public Documentacion
{
private:

    QString nombre;
    QString fecha_nacimiento;
    char genero;
    QString nacionalidad;
    QString estado_civil;

public:
    Pasaporte(QString nombre, QString fecha_nacimiento, char genero, QString nacionalidad, QString estado_civil);
    QString getnombre() const;
    QString getfecha_nacimiento() const;
    char getgenero() const;
    QString getnacionalidad() const;
    QString getestado_civil() const;

};
#endif // PASAPORTE_H
