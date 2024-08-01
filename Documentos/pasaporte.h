#ifndef PASAPORTE_H
#define PASAPORTE_H
#include "documentacion.h"
#include "../NPC/skin.h"
#include <QString>

class Pasaporte : public Documentacion
{
private:
    // Campos del DNI
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
    Skin SkinNPC;
    Skin getSkinNPC() const;
    void setSkinNPC(const Skin &newSkinNPC);
};
#endif // PASAPORTE_H
