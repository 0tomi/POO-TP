#ifndef LOCURACARACTERES_H
#define LOCURACARACTERES_H
#include <QDebug>
#include <QString>
#include <QChar>
#include <QRandomGenerator>


class LocuraCaracteres
{
public:
    LocuraCaracteres(QRandomGenerator * newGenerador);
    QString CambiarCadena(QString Cadena, int Dificultad);
    QString CambiarCadena(QString Cadena, int CantMaxCaracters, int CantMinCaracteres = 0);
private:
    QString Cambiar(QString Cadena);
    QChar CambiarNumero(QChar numeroOriginal);
    QChar CambiarLetra(QChar letraOriginal);

    QRandomGenerator * generador;
    QString cadena;
    QString cadenaNew;

    int cantMaxCaracteres;
    int cantMinCaracteres;
    void setDificultad(int Dificultad);
    int * indices;
    int * AlgoritmoDeReservoirByTomi(QString * CadenaLocura);
    /*
ReservoirSampling(conjunto, n):
    reservorio := arreglo de tamaño n
    // Llenar el reservorio con los primeros n elementos del conjunto
    para i desde 0 hasta n-1 hacer:
        reservorio[i] := conjunto[i]

    // Continuar con el resto del conjunto
    para i desde n hasta longitud(conjunto)-1 hacer:
        r := número aleatorio entre 0 y i
        si r < n entonces:
            reservorio[r] := conjunto[i]

    retornar reservorio
     */
};

#endif // LOCURACARACTERES_H
