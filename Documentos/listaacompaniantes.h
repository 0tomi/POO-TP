#ifndef LISTAACOMPANIANTES_H
#define LISTAACOMPANIANTES_H

#include <QString>
#include "documentacion.h"

class ListaAcompaniantes: public Documentacion
{
private:
    QString mensajeSinAcomp;
    QString* nombresAcomps;
    int topeNombresAcomps;
    int CantAcompaniantes;
    bool validez;
    bool dialogo;

public:
    ListaAcompaniantes();
    ListaAcompaniantes(QString mensajeSinAcomp, bool validez, bool dialogo);
    ListaAcompaniantes(QString* nombresAcomps, int topeNombresAcomps, bool validez, bool dialogo);

    // getters:
    QString getMensajeSinAcomp();
    QString* getNombresAcomps();
    int getTopeNombresAcomps();
    bool getValidez() const;
    int getCantAcompaniantes() const;
    bool getValidezDialogo() const;
};

#endif // LISTAACOMPANIANTES_H
