#ifndef REGLASNIVEL1_H
#define REGLASNIVEL1_H

#include "reglas.h"
#include "../AtributosComunes/atributoscomunes.h"
#include <QString>
#include <QRandomGenerator>

using namespace std;

class ReglasNivel1: public Reglas{
public:
    // constructores:
    ReglasNivel1(AtributosComunes *atributos);
    ReglasNivel1(AtributosComunes *atributos, int cantidadMinimaPaisesPermitidos);

    // metodos:
    void resetReglas(int cantidadMinimaPaisesPermitidos);

    // Getters
    int* getPaisesPermitidos(int &max);
    QString* getEstadoCivilPermitido(int &max);
    //QString* getTipoVisitaPermitida(int &max);
    int getFechaMinPermitida();
    int getFechaMaxPermitida();
    int getDuracionEstanciaPermitida();

    ~ReglasNivel1();

    QString *getTipoDeVisitaValida() const;

    int getMaxVisitasPermitidas() const;

private:
    // Generador de numeros
    QRandomGenerator Random;

    // # Conjunto de elementos de los cuales obtendremos las reglas #
    QString* paises;
    int maxPaises;

    QString* tipoVisitas;
    int maxTiposVisitas;

    QString* estadosCiviles;
    int maxEstadosCiviles;

    // # Conjunto de reglas #
    int fechaMin, fechaMax; // va a ser solo el anio
    int duracionDeEstanciaValida;
    int* paisesValidos;
    QString* tipoDeVisitaValida;
    QString* estadoCivilValidos;

    // Tope de arrays:
    int maxPaisesPermitidos;
    int maxEstadosCivilPermitidos;
    int maxVisitasPermitidas;

    // # Metodos para setear reglas validas #
    void setFechasValidas();
    void setDuracionEstanciaValida(int max, int min);

    void setEstadoCivilValidos();
    void SeleccionarEstadosCivilesValidos(int CantidadEstadosValidos);

    void setTipoDeVisitaValidas();
    void SeleccionarVisitasValidas(int CantidadVisitasValidas);

    void setPaisesPermitidos(int cantidadMinimaPaisesPermitidos);
    bool checkRepetidos(int dato);
};


#endif // REGLASNIVEL1_H
