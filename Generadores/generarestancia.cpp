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

    ObtenerVisitasInvalidas();

    // Inicializamos la semilla del random
    quint32 Semilla = static_cast<quint32>(time(NULL));
    NumRandom.seed(Semilla);
}

GenerarEstancia::~GenerarEstancia()
{

}

void GenerarEstancia::resetReglas(QString *TiposVisitas, int TopeVisits, QString *TiposVisitsVal, int TopeVisitsVal, int DuracMax)
{
    tipoVisitas = TiposVisitas;
    maxTipoVisitas = TopeVisits;

    tipoVisitasValidas = TiposVisitsVal;
    maxVisitasValidas = TopeVisitsVal;

    duracMaximaEstancia = DuracMax;
    ObtenerVisitasInvalidas();
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

void GenerarEstancia::ObtenerVisitasInvalidas()
{
    // Buscamos las visitas invalidas, para no tener que calcularlas despues
    bool NoValido;
    int Indice = 0;
    maxVisitasInvalidas = 0;
    // Buscamos 1x1 los tipos de visitas que hay
    for (int i = 0; i < maxTipoVisitas; i++){
        NoValido = true;
        for (int j = 0; j < maxVisitasInvalidas; j++)
            // Si el tipo de visita valida coincide con el que estamos viendo, lo damos como valido.
            if (tipoVisitasValidas[j] == tipoVisitas[i])
                NoValido = false;
        // Si es no valido, lo sumamos a nuestra lista de indices.
        if (NoValido){
            IndicesTiposVisitasInvalidas[Indice] = i;
            maxVisitasInvalidas++; Indice++;
        }
    }
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
        qDebug() << "Bucle de campos invalidos estancia";
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

    return Duracion;
}

QString GenerarEstancia::GenerarVisita(bool validez)
{
    QString Visita;
    int Sorteo;

    if (validez){
        if (maxVisitasValidas == 1) // Evitamos bugs
            Visita = tipoVisitasValidas[0];
        else {
            Sorteo = NumRandom.bounded(maxVisitasValidas);
            Visita = tipoVisitasValidas[Sorteo];
        }
    } else {
        qDebug() << "Bucle de visita falsa";
        Sorteo = NumRandom.bounded(maxVisitasInvalidas);
        // Colocamos uno de los indices de visitas invalidas.
        Visita = tipoVisitas[ IndicesTiposVisitasInvalidas[Sorteo] ];
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


