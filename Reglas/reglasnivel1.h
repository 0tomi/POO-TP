#ifndef REGLASNIVEL1_H
#define REGLASNIVEL1_H

#include "reglas.h"
#include <QString>
#include <QRandomGenerator>
#include <vector>
#include <list>

using namespace std;

class ReglasNivel1: public Reglas{
public:
    // constructores:
    ReglasNivel1();
    ReglasNivel1(quint32 Seed);
    ReglasNivel1(int cantidadMinimaPaisesPermitidos);
    ~ReglasNivel1();

    // Generadores
    void generar_Todo(int CantPaises, int CantEstadosCiviles, int RangoFechas, int DuracionEst, int CantTiposVisita);

    void generar_Paises(int Cantidad_Paises_Permitidos);
    //void generar_Paises(vector<QString>& Lista_PaisesPermitidos); STANDBY HASTA ARREGLAR OTRAS COSAS

    void generar_EstadosCiviles(int Cantidad_EstadosCiviles_Permitidos);
    //void generar_EstadosCiviles(vector<QString>& Lista_EstadosCiviles_Permitidos);

    void generar_Fechas(int Rango);
    void set_Fechas(int FechaMinima, int FechaMaxima);

    void generar_DuracionEstancia(int duracion);

    void generar_TiposVisita(int Cantidad_Visitas_Permitidas);
    //void generar_TiposVisita(vector<QString>& Lista_Visitas_Permitidas);

    // metodos:
    void resetReglas(int cantidadMinimaPaisesPermitidos, quint32 seed);

    // Getters
    vector<QString> getPaisesPermitidos() const;
    vector<QString> getEstadoCivilPermitido() const;
    vector<QString>getPaisesInvalidos() const;
    vector<QString> getEstadoCivilInvalido() const;
    //QString* getTipoVisitaPermitida(int &max);
    int getFechaMinPermitida();
    int getFechaMaxPermitida();
    int getDuracionEstanciaPermitida();

    vector<QString>getTipoDeVisitaValida() const;
    vector<QString> getTipoVisitaInvalida() const;
    int getMaxVisitasPermitidas() const;

private:
    // Para proximo rework
    list <QString> estadosCivilesValidos;
    list <QString> estadosCivilesInvalidos;
    list <QString> tiposVistaValida;
    list <QString> tiposVisitaInvalida;
    vector <QString> PaisesValidos;
    vector <QString> PaisesInvalidos;

    // # Conjunto de reglas #
    int fechaMin, fechaMax; // va a ser solo el anio
    int duracionDeEstanciaValida;
    vector<parDatos> parpaisesValidos;
    vector<parDatos> parpaisesInvalidos;
    vector<QString> tipoDeVisitaValida;
    // Tope de arrays:
    int maxPaisesPermitidos;
    int maxPaisesInvalidos;
    int maxEstadosCivilPermitidos;
    int maxVisitasPermitidas;

    // # Metodos para setear reglas validas #
    void setFechasValidas();
    void setDuracionEstanciaValida(int max, int min);

    void SumarAztana();
};
#endif // REGLASNIVEL1_H
