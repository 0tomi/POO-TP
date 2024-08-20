#ifndef REGLASNIVEL1_H
#define REGLASNIVEL1_H

#include "reglas.h"
#include <QString>
#include <QRandomGenerator>

using namespace std;

class ReglasNivel1: public Reglas{
public:
    // constructores:
    ReglasNivel1();
    ReglasNivel1(int cantidadMinimaPaisesPermitidos);
    ~ReglasNivel1();

    // metodos:
    void resetReglas(int cantidadMinimaPaisesPermitidos);

    // Getters
    int* getPaisesPermitidos(int &max) const;
    QString* getEstadoCivilPermitido(int &max) const;
    int *getPaisesInvalidos(int &max) const;
    //QString* getTipoVisitaPermitida(int &max);
    int getFechaMinPermitida();
    int getFechaMaxPermitida();
    int getDuracionEstanciaPermitida();

    QString *getTipoDeVisitaValida() const;
    int getMaxVisitasPermitidas() const;

private:
    // Generador de numeros
    QRandomGenerator Random;

    // # Conjunto de reglas #
    int fechaMin, fechaMax; // va a ser solo el anio
    int duracionDeEstanciaValida;
    int* paisesValidos;
    int* paisesInvalidos;
    QString* tipoDeVisitaValida;
    QString* estadoCivilValidos;

    // Tope de arrays:
    int maxPaisesPermitidos;
    int maxPaisesInvalidos;
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
    bool checkIfValido(int indice);

    void SumarAstana();
};


#endif // REGLASNIVEL1_H
