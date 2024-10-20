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
    quint32 seed;
};
#endif // PLAYERSTATS_H
