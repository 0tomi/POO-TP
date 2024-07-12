#include "generarestancia.h"

#include <stdlib.h>
#include <ctime>
#include <QDebug>

GenerarEstancia::GenerarEstancia(QString* TiposVisitas, int TopeVisits, QString* TiposVisitsVal, int TopeVisitsVal, int DuracMax)
{
    tipoVisitas = TiposVisitas;
    maxTipoVisitas = TopeVisits;

    tipoVisitasValidas = TiposVisitsVal;
    maxVisitasValidas = TopeVisitsVal;

    duracMaximaEstancia = DuracMax;

    // Inicializamos la semilla del random
    quint32 Semilla = static_cast<quint32>(time(NULL));
    NumRandom.seed(Semilla);
}

GenerarEstancia::~GenerarEstancia()
{

}

// getters:
Estancia* GenerarEstancia::getEstancia(bool valido, int Dificultad) {
    int Probabilidades;
    switch (Dificultad){
        // Modo facil
    case 1: Probabilidades = 7;
        break;
        // Modo demonio
    case 3: Probabilidades = 3;
        break;
        // Modo normal
    default: Probabilidades = 5;
        break;
    }

    GenerarCamposValidos(Probabilidades, valido);
    int Duracion = GenerarDuracion(ValidezCampos[0]);
    QString TipoVisita = GenerarVisita(ValidezCampos[1]);

    Estancia* estanciaAGenerar = new Estancia(Duracion, TipoVisita);
    return estanciaAGenerar;
}

void GenerarEstancia::GenerarCamposValidos(int Probabilidad, bool Validez)
{
    if (Validez){
        for (int i = 0; i < 2; ++i)
            ValidezCampos[i] = true;
    } else {
        int cantidadCamposInvalidos = 0;
        int sorteo;
        // Hasta no generarse por lo menos 1 campo valido, no sale del while.
        while (!cantidadCamposInvalidos)
            for (int i = 0; i < 2; ++i){
                sorteo = NumRandom.bounded(10);
                if (sorteo < Probabilidad){
                    ValidezCampos[i] = false;
                    cantidadCamposInvalidos++;
                }
            }
    }
}

int GenerarEstancia::GenerarDuracion(bool validez)
{
    int Duracion;
    if (validez)
        Duracion = NumRandom.bounded(3, duracMaximaEstancia+1);
    else Duracion = NumRandom.bounded(duracMaximaEstancia, duracMaximaEstancia*2);
    // ############## DEBUG ############# DEBUG ############ DEBUG ###############
    qDebug() << Duracion;
    return Duracion;
}

QString GenerarEstancia::GenerarVisita(bool validez)
{
    QString Visita;
    int Sorteo;
    // ############## DEBUG ############# DEBUG ############ DEBUG ###############
    qDebug() << maxVisitasValidas;
    if (validez){
        if (maxVisitasValidas < 2) // Evitamos bugs
            Visita = tipoVisitasValidas[0];
        else {
            Sorteo = NumRandom.bounded(maxVisitasValidas);
            Visita = tipoVisitasValidas[Sorteo];
        }
    } else {
        do{ // Repetimos hasta colocar un tipo de visita invalida.
            Sorteo = NumRandom.bounded(maxTipoVisitas);
            Visita = tipoVisitas[Sorteo];
        }while(!ComprobarInValidez(Visita));
    }
    return Visita;
}

bool GenerarEstancia::ComprobarInValidez(QString dato)
{
    for (int i = 0; i < maxVisitasValidas; i++)
        if (dato == tipoVisitasValidas[i])
            return false;
    return true;
}


