#ifndef DOCUMENTACION_H
#define DOCUMENTACION_H
#include <QString>

class Documentacion
{
public:
    Documentacion();
    virtual ~Documentacion();
    virtual QString getDatosFalsos();
    virtual void addDatosFalsos(QString datos);

private:
    QString * datosFalsos;

};

#endif // DOCUMENTACION_H
