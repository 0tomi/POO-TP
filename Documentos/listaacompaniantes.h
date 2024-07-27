#ifndef LISTAACOMPANIANTES_H
#define LISTAACOMPANIANTES_H

#include <QString>

class ListaAcompaniantes {
private:
    QString mensajeSinAcomp;
    QString* nombresAcomps;
    int topeNombresAcomps;
public:
    ListaAcompaniantes();
    ListaAcompaniantes(QString mensajeSinAcomp);
    ListaAcompaniantes(QString* nombresAcomps, int topeNombresAcomps);

    // getters:
    QString getMensajeSinAcomp();
    QString* getNombresAcomps();
    int getTopeNombresAcomps();
};

#endif // LISTAACOMPANIANTES_H
