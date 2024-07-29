#ifndef LISTAACOMPANIANTES_H
#define LISTAACOMPANIANTES_H

#include <QString>

class ListaAcompaniantes {
private:
    QString mensajeSinAcomp;
    QString* nombresAcomps;
    int topeNombresAcomps;
    bool validez;
public:
    ListaAcompaniantes();
    ListaAcompaniantes(QString mensajeSinAcomp, bool validez);
    ListaAcompaniantes(QString* nombresAcomps, int topeNombresAcomps, bool validez);

    // getters:
    QString getMensajeSinAcomp();
    QString* getNombresAcomps();
    int getTopeNombresAcomps();
};

#endif // LISTAACOMPANIANTES_H
