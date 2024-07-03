#ifndef GENERARESTANCIA_H
#define GENERARESTANCIA_H

#include <string>

#include <estancia.h>
#include <juego.h>

using namespace std;

class GenerarEstancia {
private:
    bool valido;
    string* tipoVisitas;
    int topeTipoVisitas;
    string* tipoVisitasValidas;
    int topeVisitasValidas;
    int duracMaximaEstancia;
    Juego* juego;
public:
    GenerarEstancia();
    GenerarEstancia(string*, int, string*, int, int);
    Estancia* getEstancia(bool& valido); // Estancia a generar

    // getters
    string* getTiposInvalidos(string* tiposVisitas, string* tiposVisitsVal, int &cantInvalidos);
    Juego* getClaseJuego();
    int getTopeTipoVisitas();
    int getTopeTipoVisitasVals();
    bool getValidacion();
};

#endif // GENERARESTANCIA_H
