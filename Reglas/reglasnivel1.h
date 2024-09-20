#ifndef REGLASNIVEL1_H
#define REGLASNIVEL1_H

#include "reglas.h"
#include <QString>
#include <QRandomGenerator>
#include <vector>

using namespace std;

class ReglasNivel1: public Reglas{
public:
    // constructores:
    ReglasNivel1();
    ReglasNivel1(int cantidadMinimaPaisesPermitidos);
    ~ReglasNivel1();

    // Generadores
    void generar_Paises(int Cantidad_Paises_Permitidos);
    void generar_Paises(vector<QString>& Lista_PaisesPermitidos);

    void generar_EstadosCiviles(int Cantidad_EstadosCiviles_Permitidos);
    void generar_EstadosCiviles(vector<QString>& Lista_EstadosCiviles_Permitidos);

    void generar_Fechas(int Rango);
    void set_Fechas(int FechaMinima, int FechaMaxima);

    void generar_DuracionEstancia(int duracion);

    void generar_TiposVisita(int Cantidad_Visitas_Permitidas);
    void generar_TiposVisita(vector<QString>& Lista_Visitas_Permitidas);

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
    bool ValidarNombres(vector<QString>& Lista, QString * Lista2, int max);
    bool ValidarDatos(vector<QString>& Lista, int CantidadMinima, int CantidadMax, QString * Lista2, int maxLista2);
};


#endif // REGLASNIVEL1_H
