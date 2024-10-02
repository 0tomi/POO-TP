#ifndef REGLAS_H
#define REGLAS_H
#include "../lectorarchivos.h"
#include <QString>
#include <vector>
#include <QDebug>
#include <QRandomGenerator>
#include <QTime>
class Reglas
{
public:
    Reglas();
    virtual ~Reglas();

    void setSeed(quint32);
    // Getters comunes
    QString *getPaises(int &max) const;
    QString *getTipoVisitas(int &max);
    QString *getEstadosCiviles(int &max);

protected:
    struct parDatos{
        QString dato;
        bool Insertado;
    };

    template <class Puntero>
    void LimpiarDatos(Puntero &datos);

    QRandomGenerator rand;
    QString* paises; int maxPaises;
    QString tipoVisitas[3] = {"Turismo", "Trabajo", "Estudios"};
    QString estadosCiviles[4] = {"Solter", "Casad", "Divorciad", "Viud"};
    QString * copiarVector(QString*, int max);

    const int MaxEstadosCiviles = 4;
    const int MaxTipoVisitas = 3;

    bool ValidarNombres(std::vector<QString>& Lista, QString * Lista2, int max);
    bool ValidarDatos(std::vector<QString>& Lista, int CantidadMinima, int CantidadMax, QString * Lista2, int maxLista2);
    bool checkRepetidos(std::vector<QString>& Lista, int CantidadInsertada);
    bool checkValidez(QString& dato, std::vector<QString>& Lista) const;
    bool checkValidez(QString& dato, std::list<QString>& Lista) const;

    void crearParDatos(std::vector<QString>& vectorOriginal, std::vector<parDatos>& vectorPar);
    void resetearParDatos(std::vector<parDatos>& vectorPar);
    std::vector<QString> generarVector(const std::list<QString>& lista) const;
    int checkCondiciones(int cantidad, int min, std::vector<parDatos>& vec);
    bool checkCondiciones(int min, std::vector<parDatos>& vec, std::vector<QString>& lista);
    bool checkTipado(std::vector<parDatos>& vec, std::vector<QString>& lista);
    bool checkTipado(QString& elemento, std::vector<parDatos>& vec);
    std::list<QString> generarPermitido(int cantidad, std::vector<parDatos>& vec);
    std::list<QString> generarPermitido(std::vector<QString>& Permitidos);
    std::list<QString> generarNoPermitido(std::vector<parDatos>& total);

    std::vector<QString> deshacerPar(const std::vector<parDatos>& par) const;
};

template<class Puntero>
void Reglas::LimpiarDatos(Puntero &datos)
{
    if (datos){
        delete[] datos;
        datos = nullptr;
    }
}
#endif // REGLAS_H
