#ifndef PASAPORTE_H
#define PASAPORTE_H
#include "documentacion.h"

#include <string>
#include <QLabel>
class Pasaporte : public Documentacion
{
private:
    QWidget  * cara;
    QString nombre;
    QString fecha_nacimiento;
    char genero;
    QString nacionalidad;
    QString estado_civil;

public:
    Pasaporte(QString nombre, QString fecha_nacimiento, char genero, QString nacionalidad, QString estado_civil);
    QString getnombre();
    QString getfecha_nacimiento();
    char getgenero();
    QString getnacionalidad();
    QString getestado_civil();
    QWidget * getcara();
};
#endif // PASAPORTE_H
