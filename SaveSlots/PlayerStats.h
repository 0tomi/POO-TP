#ifndef PLAYERSTATS_H
#define PLAYERSTATS_H
#include <QtCore>

struct PlayerStats{
    int Nivel;
    int Dificultad;
    int TotalSocialCredits;
    int Multas;
    int CantidadNPCsRechazados;
    int CantidadNPCsAceptados;
    int CantidadErrores;
    int tiempoPartida;
    int tiempoFondo;
    int cantNPCsPasados;
    int socialCreditsEarnedInLVL;
    int cantidadTiempoDia;
    quint32 seed;
};
#endif // PLAYERSTATS_H
