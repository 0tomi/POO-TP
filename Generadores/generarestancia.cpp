#include "generarestancia.h"
#include <ctime>
#include <QDebug>

/// ########################## Constructor ###############################

void GenerarEstancia::setSeed(quint32 seed)
{
    this->NumRandom.seed(seed);
}

GenerarEstancia::GenerarEstancia()
{
    // Inicializamos la semilla del random
    quint32 Semilla = static_cast<quint32>(time(NULL));
    NumRandom.seed(Semilla);
}

void GenerarEstancia::Inicializar(ReglasNivel1 *rules, LocuraCaracteres *randomizador, quint32 seed, int dif)
{
    this->NumRandom.seed(seed);
    this->tipoVisitas = rules->getTipoVisitas();

    tipoVisitasValidas = rules->getTipoDeVisitaValida();
    maxVisitasValidas = tipoVisitasValidas.size();

    tipoVisitasInvalidas = rules->getTipoVisitaInvalida();
    maxVisitasInvalidas = tipoVisitasInvalidas.size();

    duracMaximaEstancia = rules->getDuracionEstanciaPermitida();

    locura = randomizador;

    dificultad = dif;
    switch (dif){
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
}

/// ########################## Getters ###############################
Estancia* GenerarEstancia::generar(bool valido) {
    GenerarCamposValidos(Probabilidades, valido);
    int Duracion = GenerarDuracion(ValidezCampos[0]);
    QString TipoVisita = GenerarVisita(ValidezCampos[1]);

    Estancia* estanciaAGenerar = new Estancia(Duracion, TipoVisita, valido);
    return estanciaAGenerar;
}

/// ########################## Generadores ###############################
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
        // 50 50 que se generara
        Sorteo = NumRandom.bounded(10);
        if (Sorteo < 5){
            Sorteo = NumRandom.bounded(maxVisitasInvalidas);
            // Colocamos uno de los indices de visitas invalidas.
            Visita = tipoVisitasInvalidas[Sorteo];
        } else {
            // Ponemos cualquier texto, pero con letras cambiadas
            Sorteo = NumRandom.bounded(this->tipoVisitas.size());
            Visita = locura->CambiarCadena(dificultad, tipoVisitas[Sorteo]);
        }
    }
    return Visita;
}

