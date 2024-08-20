#ifndef REGLAS_H
#define REGLAS_H
#include <QString>
class Reglas
{
public:
    Reglas();
    virtual ~Reglas();

    // Getters comunes
    QString *getPaises(int &max) const;
    QString *getTipoVisitas(int &max);
    QString *getEstadosCiviles(int &max);

protected:
    QString* paises; int maxPaises;
    QString tipoVisitas[3] = {"Turismo", "Trabajo", "Estudios"};
    QString estadosCiviles[4] = {"Solter", "Casad", "Divorciad", "Viud"};
    QString * copiarVector(QString*, int max);

    const int MaxEstadosCiviles = 4;
    const int MaxTipoVisitas = 3;
};

#endif // REGLAS_H
